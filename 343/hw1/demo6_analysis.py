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


def max_temperature(readings : list[WeatherReading]) -> float:
    # The proper way to compute a max, if you can assume there is at least one datum in the list.
    temp = readings[0].temperature
    for i in range(1, len(readings)):
        next = readings[i]
        temp = max(temp, next.temperature)
    return temp


def min_pressure(readings: list[WeatherReading]) -> float:
    # If you can't assume there's at least one datum, you must initialize temp to the smallest legal value.

    temp = 300 # the lowest valid reading we will get from our sensor is 300 hPa.
    for reading in readings:
        temp = min(temp, reading.pressure)
    return temp


def max_humidity(readings : list[WeatherReading]) -> float:
    # Flex our Python muscles by using a comprehension to map from WeatherReadings to just their humidity.
    return max(r.humidity for r in readings)


if __name__ == "__main__":
    filename = input("Enter CSV file name: ")
    all_readings = get_readings_from_file(filename, False)

    # Perform some basic arithmetic analysis.
    print(f"Max temperature: {max_temperature(all_readings)}")
    print(f"Min pressure:    {min_pressure(all_readings)}")
    print(f"Max humidity:    {max_humidity(all_readings)}")
    