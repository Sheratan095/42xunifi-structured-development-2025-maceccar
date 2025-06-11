#include <stdio.h>
#include "critical_windows.h"

static void	run_test(const int *readings, int size, int expected, const char *test_name);

int main(int argc, char *argv[])
{
	// Test case 1: Simple critical window
	int test1[] = {60, 80, 90, 70, 100, 50, 30};
	// Window [60, 80, 90, 70, 100] has average 80 with 3 readings ≥ 70 but average < 90, so not critical
	// Window [80, 90, 70, 100, 50] has average 78 with 3 readings ≥ 70 but average < 90, so not critical
	// Window [90, 70, 100, 50, 30] has average 68 with 2 readings ≥ 70, so not critical
	run_test(test1, 7, 0, "Test 1");

	// Test case 2: Perfect critical window
	int test2[] = {90, 95, 100, 75, 100};
	// Window [90, 95, 100, 75, 100] has average 92 with 5 readings ≥ 70, so critical
	run_test(test2, 5, 1, "Test 2");

	// Test case 3: Multiple critical windows
	int test3[] = {90, 95, 100, 75, 100, 95, 80, 60, 100, 120};
	// Window [90, 95, 100, 75, 100] has average 92 with 5 readings ≥ 70, so critical
	// Window [95, 100, 75, 100, 95] has average 93 with 5 readings ≥ 70, so critical
	// Window [100, 75, 100, 95, 80] has average 90 with 5 readings ≥ 70, so critical
	// Window [75, 100, 95, 80, 60] has average 82 with 4 readings ≥ 70 but average < 90, so not critical
	// Window [100, 95, 80, 60, 100] has average 87 with 4 readings ≥ 70 but average < 90, so not critical
	// Window [95, 80, 60, 100, 120] has average 91 with 4 readings ≥ 70, so critical (all readings < 150)
	run_test(test3, 10, 4, "Test 3");  // Fixed: Changed expected from 3 to 4

	// Test case 4: Exceeding max threshold (150)
	int test4[] = {90, 95, 151, 75, 100};
	// Window [90, 95, 151, 75, 100] has one reading > 150, so not critical
	run_test(test4, 5, 0, "Test 4");
	
	// Test case 5: Not enough critical days
	int test5[] = {95, 100, 60, 65, 130};
	// Window [95, 100, 60, 65, 130] has average 90 with only 3 readings ≥ 70, so critical
	// (95, 100, and 130 are all ≥ 70, and average is exactly 90)
	run_test(test5, 5, 1, "Test 5");  // Fixed: Changed expected from 0 to 1
	
	// Test case 6: Empty array
	int test6[] = {};
	run_test(test6, 0, 0, "Test 6");

	// Test case 7: Borderline case - exactly at thresholds
	int test7[] = {70, 70, 70, 70, 130, 65, 69, 149, 69, 70};
	// Window [70, 70, 70, 70, 130] has average 82 with 4 readings = 70, so not critical (avg < 90)
	// Window [70, 70, 70, 130, 65] has average 81 with 3 readings >= 70, so not critical (avg < 90)
	// Window [70, 70, 130, 65, 69] has average 80.8 with 3 readings >= 70, so not critical (avg < 90)
	// Window [70, 130, 65, 69, 149] has average 96.6 with 3 readings >= 70, so critical
	// Window [130, 65, 69, 149, 69] has average 96.4 with 2 readings >= 70, so not critical (not enough critical days)
	// Window [65, 69, 149, 69, 70] has average 84.4 with 2 readings >= 70, so not critical (not enough critical days)
	run_test(test7, 10, 1, "Test 7 - Borderline thresholds");

	// Test case 8: Exactly 90 average with enough critical days
	int test8[] = {90, 90, 90, 90, 90};
	// Window [90, 90, 90, 90, 90] has average exactly 90 with 5 readings >= 70, so critical
	run_test(test8, 5, 1, "Test 8 - Exactly 90 average");

	// Test case 9: Almost critical windows
	int test9[] = {89, 89, 89, 90, 92, 70, 70, 70, 140, 20};
	// Window [89, 89, 89, 90, 92] has average 89.8 with 2 readings >= 70, so not critical (avg < 90 and not enough days)
	// Window [89, 89, 90, 92, 70] has average 86 with 3 readings >= 70, so not critical (avg < 90)
	// Window [89, 90, 92, 70, 70] has average 82.2 with 4 readings >= 70, so not critical (avg < 90)
	// Window [90, 92, 70, 70, 70] has average 78.4 with 4 readings ≥ 70, so not critical (avg < 90)
	// Window [92, 70, 70, 70, 140] has average 88.4 with 4 readings ≥ 70, so not critical (avg < 90)
	// Window [70, 70, 70, 140, 20] has average 74 with 3 readings ≥ 70, so not critical (avg < 90)
	run_test(test9, 10, 0, "Test 9 - Almost critical windows");

	// Test case 10: Alternating pattern with critical windows
	int test10[] = {150, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 150, 90};
	// Window [150, 90, 91, 92, 93] has average 103.2 with 5 readings ≥ 70, so critical (150 is acceptable)
	// Window [90, 91, 92, 93, 94] has average 92 with 5 readings ≥ 70, so critical
	// Window [91, 92, 93, 94, 95] has average 93 with 5 readings ≥ 70, so critical
	// Window [92, 93, 94, 95, 96] has average 94 with 5 readings ≥ 70, so critical
	// Window [93, 94, 95, 96, 97] has average 95 with 5 readings ≥ 70, so critical
	// Window [94, 95, 96, 97, 98] has average 96 with 5 readings ≥ 70, so critical
	// Window [95, 96, 97, 98, 99] has average 97 with 5 readings ≥ 70, so critical
	// Window [96, 97, 98, 99, 150] has average 108 with 5 readings ≥ 70, so critical (150 is acceptable)
	// Window [97, 98, 99, 150, 90] has average 106.8 with 5 readings ≥ 70, so critical (150 is acceptable)
	run_test(test10, 13, 9, "Test 10 - Alternating pattern with 150 as acceptable");

	// Test case 11: Random edge case - lots of 69 (just below critical) and 151 (just above max)
	int test12[] = {69, 90, 69, 90, 69, 151, 90, 90, 90, 90, 90};
	// Window [69, 90, 69, 90, 69] has average 77.4 with 2 readings >= 70, so not critical
	// Window [90, 69, 90, 69, 151] has average 93.8 with 3 readings >= 70, but exceeds max, so not critical
	// Window [69, 90, 69, 151, 90] has average 93.8 with 3 readings >= 70, but exceeds max, so not critical
	// Window [90, 69, 151, 90, 90] has average 98 with 4 readings >= 70, but exceeds max, so not critical
	// Window [69, 151, 90, 90, 90] has average 98 with 4 readings >= 70, but exceeds max, so not critical
	// Window [151, 90, 90, 90, 90] has average 102.2 with 4 readings >= 70, but exceeds max, so not critical
	// Window [90, 90, 90, 90, 90] has average 90 with 5 readings ≥ 70, so critical
	run_test(test12, 11, 1, "Test 11 - Edge cases");

	return 0;
}

static void	run_test(const int *readings, int size, int expected, const char *test_name)
{
	int result = count_critical_windows(readings, size);
	printf("%s: %s (Expected: %d, Got: %d)\n", 
		   test_name,
		   result == expected ? "PASS" : "FAIL",
		   expected, result);
}