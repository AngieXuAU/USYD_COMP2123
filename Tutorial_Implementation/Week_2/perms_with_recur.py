
def permutation(arr, position):
    # base case
    if len(arr) - 1 == position:
        print(arr)
    
    else: 
        # choose a candidate
        for j in range(position, len(arr)):
            # put the candidate to the i-th position
            arr[position], arr[j] = arr[j], arr[position]

            # permutate the rest after fixing current i-th position
            permutation(arr, position + 1)
            arr[position], arr[j] = arr[j], arr[position]

permutation([1, 2, 3, 4], 0)