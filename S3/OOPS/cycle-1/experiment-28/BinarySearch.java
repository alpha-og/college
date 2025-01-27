/*
 * Experiment - 28
 * Binary Search
 * Athul Anoop
 * 07-10-24
 */

public class BinarySearch {
	public static void main(String args[]){
		int arr[] = {8,4,15,0,-2,10,6};
		int query = 10;
		for (int i = 0; i<arr.length; i++){
			for (int j = 0; j < arr.length - i - 1;j++){
				if (arr[j] > arr[j+1]){
					int tmp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = tmp;
				}
			}
		}
		System.out.printf("Array: [");
		for (int i = 0; i<arr.length; i++){
			System.out.printf("%d, ",arr[i]);
		}
		System.out.println("]");
		int beg = 0;
		int end = arr.length - 1;
		int mid = (end-beg)/2;
		while (beg != end){
			if (arr[mid] == query){
				break;
			} else if (query > arr[mid]){
				beg = mid+1;
				mid = (end-beg)/2 + beg;
				continue;
			} else if ( query < arr[mid]){
				end = mid - 1;
				mid = (end-beg)/2;
			}
		}
		System.out.printf("Query: %d | Result: found value at index %d\n",query,mid);

	}
}
