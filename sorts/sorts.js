// Compare running time for sorting algorithms
// Cheyanna Graham
// June 10, 2019

const myArr = require('./array.js').myArr;


// Bubble highest value to end of array
// Sort in place
const bubbleSort = arr => {
    let high;
    let length = arr.length;

    for (let i = 0; i < length; i++) {
        for (let j = 0; j < length - i; j++) {
            if (arr[j] > arr[j + 1]) {
                high = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = high;
            }
        }
    }

    return arr;
};

const selectionSort = arr => {
    let low, index;
    let length = arr.length;

    for (let i = 0; i < length; i++) {
        low = arr[i];
        index = i;
        // Get lowest value and index in array
        for (let j = i; j < length; j++) {
            if (arr[j] < low) {
                low = arr[j];
                index = j;
            }
        }
        arr[index] = arr[i];
        arr[i] = low;
    }

    return arr;
};

const insertionSort = arr => {
    let length = arr.length;
    let high;

    for (let i = 0; i < length; i++) {
        // Fitting arr[i] into sorted section
        for (let j = 0; j < i; j++) {
            if (arr[i] < arr[j]) {
                high = arr[j];
                arr[j] = arr[i];
                arr[i] = high;
            }
        }
    }

    return arr;
};

const mergeSort = arr => {

    let length = arr.length;
    let half = Math.floor(length / 2);

    // Recursively split array into left and right arrays until the arrays are 1 element long
    if (length > 1) {
        let split = [arr.slice(0, half), arr.slice(half, length)];
        return merge(split.map(ar => mergeSort(ar)));
    }
    return arr;
};

// Merge Left and right sides of array into 1 sorted array
const merge = ([left, right]) => {
    let newArr = [];
    let lLength = left.length;
    let rLength = right.length;
    let i = 0,
        j = 0;

    while (i < lLength && j < rLength) {
        if (left[i] < right[j]) {
            newArr.push(left[i]);
            i++;
        } else if (left[i] > right[j]) {
            newArr.push(right[j]);
            j++;
        }
    }

    if (left[i]) {
        newArr.push(...left.slice(i));
    } else if (right[i]) {
        newArr.push(...right.slice(j));
    }
    return newArr;
};

// Time function executions
const timer = (funcs) => {

    funcs.forEach(f => {
        console.time(f.name);
        f.func(f.params);
        console.timeEnd(f.name);

    });
}

let funcs = [
    {
        name:'bubbleSort',
        params: [...myArr],
        func: bubbleSort
    },
    {
        name:'selectionSort',
        params: [...myArr],
        func: selectionSort
    },
    {
        name:'insertionSort',
        params: [...myArr],
        func: insertionSort
    },
    {
        name:'mergeSort',
        params: [...myArr],
        func: mergeSort
    }
]

timer(funcs);

