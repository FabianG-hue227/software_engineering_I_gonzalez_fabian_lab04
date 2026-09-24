#include <stdio.h>
#include <ctype.h>

/* Convert a temperature in the given scale ('C','F','K') to Celsius */
static double toCelsius(double value, char scale) {
    switch (scale) {
        case 'C':
            return value;
        case 'F':
            return (value - 32.0) * 5.0 / 9.0;
        case 'K':
            return value - 273.15;
    }
    return value; /* unreachable if scale validated */
}

/* Convert a Celsius value to the given target scale ('C','F','K') */
static double fromCelsius(double celsius, char scale) {
    switch (scale) {
        case 'C':
            return celsius;
        case 'F':
            return celsius * 9.0 / 5.0 + 32.0;
        case 'K':
            return celsius + 273.15;
    }
    return celsius; /* unreachable if scale validated */
}

/* Return the category name based on a Celsius value */
static const char *categorize(double celsiusValue) {
    if (celsiusValue < 0.0) {
        return "Freezing";
    } else if (celsiusValue < 10.0) {
        return "Cold";
    } else if (celsiusValue < 25.0) {
        return "Comfortable";
    } else if (celsiusValue < 35.0) {
        return "Hot";
    } else {
        return "Extreme Heat";
    }
}

/* Small helper to compare category strings */
static int strcmpCat(const char *a, const char *b) {
    while (*a && *b) {
        if (*a != *b) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

/* Return a weather advisory string based on the category */
static const char *advisory(const char *category) {
    if (strcmpCat(category, "Freezing")) {
        return "Bundle up!";
    } else if (strcmpCat(category, "Cold")) {
        return "Wear a jacket!";
    } else if (strcmpCat(category, "Comfortable")) {
        return "Enjoy the nice weather!";
    } else if (strcmpCat(category, "Hot")) {
        return "Drink lots of water!";
    } else {
        return "Stay indoors and stay hydrated!";
    }
}

/* Read a scale character (C, F, or K), case-insensitive, re-prompting on bad input */
static char readScale(const char *prompt) {
    char buf[16];
    char scale;

    while (1) {
        printf("%s", prompt);
        if (scanf("%15s", buf) != 1) {
            continue;
        }
        scale = (char) toupper((unsigned char) buf[0]);
        if (scale == 'C' || scale == 'F' || scale == 'K') {
            return scale;
        }
        printf("Invalid scale. Please enter C, F, or K.\n");
    }
}


void runTemperatureConverter(void) {
    char again = 'Y';

    while (toupper((unsigned char) again) == 'Y') {
        double value, celsiusValue, converted;
        char fromScale, toScale;

        printf("Enter the temperature value: ");
        while (scanf("%lf", &value) != 1) {
            printf("Invalid number. Enter the temperature value: ");
            while (getchar() != '\n') { /* clear bad input */ }
        }

        fromScale = readScale("Enter the original scale (C, F, or K): ");
        toScale = readScale("Enter the scale to convert to (C, F, or K): ");

        celsiusValue = toCelsius(value, fromScale);
        converted = fromCelsius(celsiusValue, toScale);

        printf("Converted temperature: %.2f %c\n", converted, toScale);

        const char *category = categorize(celsiusValue);
        printf("Temperature category: %s\n", category);
        printf("Weather advisory: %s\n", advisory(category));

        printf("\nWould you like to perform another conversion? (Y/N): ");
        scanf(" %c", &again);
        printf("\n");
    }
}

int main(void) {
    runTemperatureConverter();
    return 0;
}