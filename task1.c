#include <stdio.h>

void possibilities(void) {
    int score;

    while (1) {
        printf("Enter the NFL score (Enter 1 to stop): ");
        if (scanf("%d", &score) != 1) {
            /* bad input, bail out */
            break;
        }

        if (score == 1) {
            break;
        }

        if (score < 0) {
            printf("Please enter a non-negative score.\n\n");
            continue;
        }

        printf("Possible combinations of scoring plays if a team's score is %d:\n", score);

        int found = 0;

        /* a = number of TD+2pt (8), b = number of TD+FG (7),
           c = number of TD (6), d = number of 3pt FG (3),
           remaining points are covered by 2pt Safeties */
        for (int a = 0; 8 * a <= score; a++) {
            for (int b = 0; 8 * a + 7 * b <= score; b++) {
                for (int c = 0; 8 * a + 7 * b + 6 * c <= score; c++) {
                    for (int d = 0; 8 * a + 7 * b + 6 * c + 3 * d <= score; d++) {
                        int remainder = score - (8 * a + 7 * b + 6 * c + 3 * d);

                        if (remainder % 2 == 0) {
                            int safety = remainder / 2;
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
                                   a, b, c, d, safety);
                            found = 1;
                        }
                    }
                }
            }
        }

        if (!found) {
            printf("No combination of scoring plays produces this score.\n");
        }

        printf("\n");
    }
}

int main(void) {
    possibilities();
    return 0;
}