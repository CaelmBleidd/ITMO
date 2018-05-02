package search;

public class BinarySearch {
    public static void main(String[] args) {
        try {
            int value = Integer.parseInt(args[0]);
            final int size = args.length - 1;
            int[] array = new int[size];
            for (int i = 0; i < size; ) {
                array[i++] = Integer.parseInt(args[i]);
            }
            int result;
            System.out.println((result = recursiveBinarySearch(array, value, 0, size)) == iterativeBinarySearch(array, value, 0, size) ? result : "Error");
        } catch (NumberFormatException e) {
            System.out.println("Wrong value in input array");
        }

    }

    //Pre: i == 0..(size - 1) && array[i - 1] >= array[i], leftBound
    //Post: Result == i && array[result - 1] > value >= array[result]
    //Post: Result == 0 ? Value = max(array[0]..array[size - 1])
    //Post: for all i in range(0..size-1) array[i] == array[i]'
    private static int recursiveBinarySearch(final int[] array, final int value, int leftBound, int rightBound) {
        // Inv: array[0]..array[leftBound] > value >= array[rightBound]..array[size]
        // if rightBound == leftBound, rightBound = min(0...size - 1) && array[rightBound] >= value
        if (leftBound < rightBound) {
            //Inv && leftBound < rightBound
            int mid = (leftBound + rightBound) >> 1;
            // leftBound <= mid < rightBound
            if (array[mid] > value) {
                leftBound = mid + 1;
                // Inv && value < array[mid]
                // array[-1]...array[mid] > array[mid] >= array[rightBound]...array[size]
            } else {
                // Inv && value >= array[mid]
                // array[-1]...array[leftBound-1] >= array[mid] > array[rightBound]...array[size]
                rightBound = mid;
            }
            //Inv && array[-1]..array[leftBound] > value >= array[rightBound]..array[size]
            return recursiveBinarySearch(array, value, leftBound, rightBound);
        } else {
            //Inv && leftBound >= rightBound
            //array[leftBound - 1] > value >= array[rightBound]
            //array[rightBound - 1] > value >= array[rightBound]
            //Result = rightBound

            return rightBound;
        }
    }

    //Pre: i == 0..(size - 1) && array[i - 1] >= array[i]
    //Post: Result == i && array[result - 1] > value >= array[result]
    //Post: Result == 0 ? Value = max(array[0]..array[size - 1])
    //Post: for all i in range(0..size-1) array[i] == array[i]'
    private static int iterativeBinarySearch(final int[] array, final int value, int leftBound, int rightBound) {
        // Inv: array[-1]...array[leftBound-1] > value >= array[rightBound]....array[size]
        // if rightBound = leftBound, rightBound = min(-1...size) && array[rightBound] >= value
        while (leftBound < rightBound) {
            // Inv && leftBound < rightBound
            int mid = (leftBound + rightBound) >>> 1;
            //  leftBound <= mid < rightBound
            if (array[mid] <= value)
                // Inv && value >= array[mid]
                rightBound = mid;
                // array[-1]...array[leftBound-1] >= array[mid] > array[rightBound]...array[size]
            else
                // Inv && value < array[mid]
                leftBound = mid + 1;
            // array[-1]...array[mid] > array[mid] >= array[rightBound]...array[size]
        }
        //Inv && leftBound >= rightBound
        //array[leftBound] > value >= array[rightBound]
        //array[rightBound - 1] > value >= array[rightBound]
        //Result = rightBound
        return rightBound;
    }
}
