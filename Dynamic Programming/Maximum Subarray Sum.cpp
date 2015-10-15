/* Given an array o fintegeres A to length n, 
 * find the interval indicies and and b such that
 * sum i = a to b A[i] is maximized
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

pair<int, int> FindMaximumSubArray (const vector<int>& Arr) {
	// Arr[range.first : range.second - 1] will be the maximum subarrary
	pair<int, int> range(0, 0);
	int minIndex = -1, minSum = 0, sum = 0, maxSum = 0;
	for (int i = 0; i < Arr.size(); i++) {
		sum += Arr[i];
		if (sum < minSum) {
			minSum = sum;
			minIndex = i;
		}
		if (sum - minSum > maxSum) {
			maxSum = sum - minSum;
			range = {minIndex + 1, i + 1};
		}
	}
	return range;
}