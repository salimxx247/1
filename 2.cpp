#include <stdio.h>

// --- Section A: Data & Calculations ---

// Function to calculate efficiency (km per litre)
float calculateEfficiency(float distance, float fuel) {
    return distance / fuel;
}

// --- Section B: Decision Making ---

// Function to determine the efficiency category
char tripCategory(float efficiency) {
    if (efficiency >= 12.0) {
        return 'E';
    } else if (efficiency >= 8.0) {
        return 'A';
    } else {
        return 'P';
    }
}

// Function to print a recommendation based on the category
void printRecommendation(char category) {
    switch (category) {
        case 'E':
            printf("  Recommendation: Great job! Keep it up.\n");
            break;
        case 'A':
            printf("  Recommendation: Decent efficiency. Try to improve.\n");
            break;
        case 'P':
            printf("  Recommendation: Efficiency is poor. Check for issues.\n");
            break;
        default:
            printf("  Recommendation: Unknown category.\n");
    }
}

// --- Section D: Functions in Depth ---

// Function to display one trip's line in the report (no return value)
void displayTripReport(int tripNumber, float distance, float fuel, float efficiency, char category) {
    printf("Trip %d: Distance = %.2f km, Fuel = %.2f L, Efficiency = %.2f km/L, Category = %c\n",
           tripNumber, distance, fuel, efficiency, category);
}

// Function to update the best and worst efficiency using pass-by-reference (pointers)
void updateBestAndWorst(float efficiency, float *bestEfficiency, float *worstEfficiency) {
    // If it's the first trip (initialized to -1), set both to the first efficiency
    if (*bestEfficiency == -1 && *worstEfficiency == -1) {
        *bestEfficiency = efficiency;
        *worstEfficiency = efficiency;
    } else {
        if (efficiency > *bestEfficiency) {
            *bestEfficiency = efficiency;
        }
        if (efficiency < *worstEfficiency) {
            *worstEfficiency = efficiency;
        }
    }
}

// --- Main Program ---
int main() {
    float distance, fuel, efficiency;
    char category;
    int tripCount = 0;
    int poorStreak = 0; // Counter for consecutive poor trips
    char lastCategory = '\0'; // Track the category of the last trip

    // Variables to store the best and worst efficiencies (initialized to -1)
    float bestEfficiency = -1.0;
    float worstEfficiency = -1.0;

    printf("--- Workshop Fuel Efficiency Tracker ---\n");
    printf("Enter trip data (Distance in km, Fuel in L).\n");
    printf("Enter -1 for distance to end the shift.\n\n");

    // --- Section C: Loops & Loop Control ---

    while (1) {
        // Get distance from the user
        printf("Enter distance for trip %d (or -1 to stop): ", tripCount + 1);
        scanf("%f", &distance);

        // Check for the end-of-shift signal
        if (distance == -1) {
            break;
        }

        // Get fuel used from the user
        printf("Enter fuel used for trip %d (in litres): ", tripCount + 1);
        scanf("%f", &fuel);

        // Section C, point 6: Validate fuel input
        if (fuel <= 0) {
            printf("Error: Fuel used must be a positive number. Trip cannot be processed.\n\n");
            continue; // Skip to the next trip
        }

        // --- Calculations and Processing ---

        // Calculate efficiency
        efficiency = calculateEfficiency(distance, fuel);

        // Determine the category
        category = tripCategory(efficiency);

        // --- Section D, point 8: Display the trip report ---
        tripCount++;
        displayTripReport(tripCount, distance, fuel, efficiency, category);

        // --- Section B, point 4: Print recommendation using switch ---
        printRecommendation(category);

        // --- Section D, point 9: Update best and worst efficiency ---
        updateBestAndWorst(efficiency, &bestEfficiency, &worstEfficiency);

        // --- Section C, point 7: Check for consecutive poor trips ---
        if (category == 'P') {
            // Check if the previous trip was also 'P'
            if (lastCategory == 'P') {
                poorStreak++;
                // If this is the second consecutive poor trip, trigger the warning
                if (poorStreak >= 2) {
                    printf("\n*** URGENT WARNING: Truck is under-performing consecutively! ***\n");
                    printf("*** Service is required immediately. Ending shift. ***\n");
                    break; // Stop taking further trips
                }
            } else {
                // This is the first poor trip after a non-poor trip, reset streak
                poorStreak = 1;
            }
        } else {
            // Reset the streak if the trip is not poor
            poorStreak = 0;
        }

        // Store the category of the current trip for the next iteration
        lastCategory = category;
        printf("\n"); // Add a blank line for readability
    }

    // --- End of Shift Summary ---
    printf("\n--- End of Shift Report ---\n");
    if (tripCount > 0) {
        printf("Total trips processed: %d\n", tripCount);
        printf("Best efficiency: %.2f km/L\n", bestEfficiency);
        printf("Worst efficiency: %.2f km/L\n", worstEfficiency);
    } else {
        printf("No trips were processed during this shift.\n");
    }

    return 0;
}
