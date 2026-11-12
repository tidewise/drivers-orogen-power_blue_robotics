# frozen_string_literal: true

using_task_library "power_blue_robotics"
import_types_from "raw_io"

describe OroGen.power_blue_robotics.PowerSenseModuleTask do
    run_live

    attr_reader :task

    before do
        @task = syskit_deploy(
            OroGen.power_blue_robotics.PowerSenseModuleTask
                  .deployed_as("power_sense_module_test")
        )
    end

    it "outputs voltage and current scaled with default parameters" do
        syskit_configure_and_start(task)

        now = Time.now
        time_voltage = now
        time_current = now - 1

        samples = create_analog_samples(
            [
                [now, 0.0],
                [now, 0.0],
                [time_current, 0.5],
                [time_voltage, 1.2]
            ]
        )

        voltage_sample, current_sample =
            expect_execution { syskit_write task.analog_samples_port, samples }
            .to do
                [have_one_new_sample(task.voltage_port),
                 have_one_new_sample(task.current_port)]
            end

        expected_voltage = 1.2 * 11.0 
        assert_in_delta expected_voltage, voltage_sample.value, 1e-4
        assert_in_delta time_voltage, voltage_sample.time, 1e-4
        expected_current = (0.5 - 0.33) * 37.8788
        assert_in_delta expected_current, current_sample.value, 1e-4
        assert_in_delta time_current, current_sample.time, 1e-4
    end

    it "transitions to exception state if the input vector has insufficient readings" do
        syskit_configure_and_start(task)

        now = Time.now
        samples = create_analog_samples(
            [
                [now, 0.0],
                [now, 0.0]
            ]
        )

        expect_execution { syskit_write task.analog_samples_port, samples }
            .to_emit task.invalid_analog_samples_event
    end

    it "transitions to exception state if the input vector is empty" do
        syskit_configure_and_start(task)

        expect_execution { syskit_write task.analog_samples_port, [] }
            .to_emit task.invalid_analog_samples_event
    end

    def create_analog_sample(time, data)
        sample = Types.raw_io.Analog.new
        sample.time = time
        sample.data = data
        sample
    end

    def create_analog_samples(readings)
        readings.map { |time, data| create_analog_sample(time, data) }
    end
end
