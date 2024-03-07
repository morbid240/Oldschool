# Data Lifecycle: Storage.
# Reading from a CSV file.
from weatherreading import WeatherReading


def valid_temperature(temperature : float):
    return -40 < temperature < 85


def valid_pressure(pressure : float):
    return 300 < pressure < 1200


def valid_humidity(humidity : float):
    return 20 < humidity < 80


def valid_reading(temperature : float, pressure : float, humidity : float):
    return valid_temperature(temperature) and valid_pressure(pressure) and valid_humidity(humidity)


def get_readings_from_file(filename : str, skip_first_line : bool) -> list[WeatherReading]:
    with open(filename, "r") as file:
        all_readings : list[WeatherReading] = []
        first_line = True

        for line in file:
            if skip_first_line and first_line:
                continue

            split = line.split(",")
            temperature = float(split[0])
            pressure = float(split[1])
            humidity = float(split[2])
            if valid_reading(temperature, pressure, humidity):
                reading = WeatherReading(temperature, pressure, humidity)
                all_readings.append(reading)
    
        return all_readings


if __name__ == "__main__":
    filename = input("Enter CSV file name: ")
    all_readings = get_readings_from_file(filename, False)

    # Echo the input to output.
    print("Your readings:")
    for reading in all_readings:
        print(f"\tTemp: {reading.temperature}", end="")
        print(f"\tPressure: {reading.pressure}", end="")
        print(f"\tHumidity: {reading.humidity}")