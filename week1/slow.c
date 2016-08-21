/*
 * Made by Utkrisht Dhankar
 * Roll number B15138
 * Compile with gcc `pkg-config --cflags --libs glib-2.0` -lm -g -o slow slow.c 
 */

#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <glib.h>

#define MAX_PIXEL_VALUE 255

// Returned by the thresholding functions
struct threshold_data
{
	// The number of elements in each cluseter
	int num_low;
	int num_high;

	// The means of the lower and higher clusters
	float mean_low;
	float mean_high;

	// The standard deviations of the clusters
	float sd_low;
	float sd_high;

	// The ratio of number of elements in the high cluster
	// to those in the low cluster
	float ratio;

	// Discriminative Index
	float disc_index;
};


// Thresholds the data and returns the calculated output
struct threshold_data compute_threshold(GArray *array, int threshold);

int main()
{
	printf("Reading the input data...\n");

	// Use to keep track of time elapsed
	GTimer *timer = g_timer_new();

	FILE *data_file = fopen("data.txt", "r");

	// We can't use a 2D matrix because we don't know the size
	// This array will NOT be 0 terminated,
	// and WILL initialize all elements to 0
	GArray * data = g_array_new(FALSE, TRUE, sizeof(int));

	// Fill the data array with data from the file
	int temp;
	while (!feof(data_file)) {
		fscanf(data_file, "%d ", &temp);
		g_array_append_val(data, temp);
	}

	fclose(data_file);

	double elapsed = g_timer_elapsed(timer, NULL);
	printf("Data read in %lf ms\n\n", elapsed * 1000.0);

	printf("Performing iterative thresholding .........\n");

	// Restart the clock to measure the thresholding time
	g_timer_start(timer);

	// We'll store the threshold data here
	GArray *threshold_array = g_array_new(FALSE, TRUE,
			sizeof(struct threshold_data));

	int threshold;
	for (threshold = 0; threshold <= MAX_PIXEL_VALUE; threshold++) {
		// We have to use a variable here as
		// g_array_append_val needs a reference
		struct threshold_data tmp_data = compute_threshold(data,
				threshold);
		g_array_append_val(threshold_array, tmp_data);
	}

	elapsed = g_timer_elapsed(timer, NULL);
	printf("Thresholding done in %lf ms\n\n", elapsed * 1000.0);

	// Store the result in a file
	FILE *results_file = fopen("result.dat", "w");
	for (threshold = 0; threshold <= MAX_PIXEL_VALUE; threshold++) {
		fprintf(results_file, "%d\t%lf\t%lf\n",
			threshold,
			g_array_index(threshold_array, struct threshold_data,
				threshold).disc_index,
			g_array_index(threshold_array, struct threshold_data,
				threshold).ratio);
	}

	fclose(results_file);

	// Plot th vs d' using gnuplot
	int i;
	FILE * gnuplot_pipe = popen ("gnuplot -persistent", "w");
	fprintf(gnuplot_pipe, "set title \"th vs d'\"\n"
				"set terminal png\n"
				"set output \"a.png\"\n");
	fprintf(gnuplot_pipe, "plot '-' \n");
	for (i = 0; i < MAX_PIXEL_VALUE + 1; i++)
	{
		fprintf(gnuplot_pipe, "%d %lf\n", i,
			g_array_index(threshold_array,
				struct threshold_data, i).disc_index);
	}
	fprintf(gnuplot_pipe, "e\n");
	/* fclose(gnuplot_pipe); */

	// Plot th vs np using gnuplot
	/* gnuplot_pipe = popen ("gnuplot -persistent", "w"); */
	fprintf(gnuplot_pipe, "set title \"th vs np\"\n"
				"set terminal png\n"
				"set output \"b.png\"\n");
	fprintf(gnuplot_pipe, "plot '-' \n");
	for (i = 0; i < MAX_PIXEL_VALUE + 1; i++)
	{
		fprintf(gnuplot_pipe, "%d %lf\n", i,
			g_array_index(threshold_array,
				struct threshold_data, i).ratio);
	}
	fprintf(gnuplot_pipe, "e\n");
	/* fclose(gnuplot_pipe); */

	// Plot th vs np using gnuplot
	/* gnuplot_pipe = popen ("gnuplot -persistent", "w"); */
	fprintf(gnuplot_pipe, "set title \"d' vs np\"\n"
				"set terminal png\n"
				"set output \"c.png\"\n");
	fprintf(gnuplot_pipe, "plot '-' \n");
	for (i = 0; i < MAX_PIXEL_VALUE + 1; i++)
	{
		fprintf(gnuplot_pipe, "%lf %lf\n",
			g_array_index(threshold_array,
				struct threshold_data, i).disc_index,
			g_array_index(threshold_array,
				struct threshold_data, i).ratio);
	}
	fprintf(gnuplot_pipe, "e\n");
	fclose(gnuplot_pipe);

	// Free the data we held
	g_array_free(threshold_array, TRUE);
	return 0;
}

// Clusters the data stored in the array and stores it in the two
// passed linked lists. Any data in these two lists is LOST!
void cluster_data(GArray *data, int threshold, GSList **low, GSList **high)
{
	// Create empty lists out of the two pointers
	*low = NULL;
	*high = NULL;

	// Cluster data
	int i;
	for (i = 0; i < data->len; i++) {
		if (g_array_index(data, int, i) <= threshold)
			*low = g_slist_prepend(*low, &g_array_index(data, int, i));
		else
			*high = g_slist_prepend(*high, &g_array_index(data, int, i));
	}
}

struct threshold_data compute_threshold(GArray *array, int threshold)
{
	// Cluster the data
	GSList *low, *high;
	cluster_data(array, threshold, &low, &high);

	// Initialize the calculated data
	struct threshold_data calculated;
	calculated.num_low = 0;
	calculated.num_high = 0;

	// Calculate the sums and number of elements of the two clusters
	int low_sum = 0, high_sum = 0;
	int low_squared_sum = 0, high_squared_sum = 0;

	GSList *it;
	for (it = low; it; it = it->next) {
		calculated.num_low++;
		low_sum += *((int*) it->data);
		low_squared_sum += *((int*) it->data) * *((int*) it->data);
	}

	for (it = high; it; it = it->next) {
		calculated.num_high++;
		high_sum += *((int*) it->data);
		high_squared_sum += *((int*) it->data) * *((int*) it->data);
	}

	// Free the cluster lists, we don't need them now
	g_slist_free(low);
	g_slist_free(high);

	// Calculate means
	if (calculated.num_low > 0) {
		calculated.mean_low = (float) low_sum
			/ (float) calculated.num_low;
	} else {
		calculated.mean_low = 0;
	}

	if (calculated.num_high > 0) {
		calculated.mean_high = (float) high_sum
			/ (float) calculated.num_high;
	} else {
		calculated.mean_high = 0;
	}

	// Calculate variances
	float variance_low;
	float variance_high;
	if (calculated.num_low > 0) {
		variance_low = fabs(low_squared_sum / calculated.num_low
			- calculated.mean_low * calculated.mean_low);
	} else {
		variance_low = 0;
	}

	if (calculated.num_high > 0) {
		variance_high = fabs(high_squared_sum / calculated.num_high
			- calculated.mean_high * calculated.mean_high);
	} else {
		variance_high = 0;
	}

	// Calculate standard deviations
	calculated.sd_low = sqrt(variance_low);
	calculated.sd_high = sqrt(variance_high);

	// Calculate ratio
	if (calculated.num_high > 0) {
		calculated.ratio = (float) calculated.num_low
			/ (float) calculated.num_high;
	} else {
		calculated.ratio = 0;
	}

	// Calculate discriminative index
	calculated.disc_index = fabs(calculated.mean_high
			- calculated.mean_low)
			/ sqrt(variance_low + variance_high);

	return calculated;
}
