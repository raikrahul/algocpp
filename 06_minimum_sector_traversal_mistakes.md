# MISTAKE LOG

## ERROR 1: DUPLICATE LOOP
Line 62-72: First for loop (i=0 to n-1)
Line 74-85: Second for loop NESTED INSIDE first loop, DUPLICATE code
What went wrong: Copy-pasted entire loop instead of adding CCW-then-CW code
What should be: Single loop with both CW-then-CCW AND CCW-then-CW calculations
Why sloppy: Failed to read instruction "ADD THIS inside the for loop"
What missed: "inside" means APPEND to existing loop, not CREATE new loop
How to prevent: Read location instruction (after line X, inside block Y)

## ERROR 2: MISSING CCW-THEN-CW STRATEGY
Line 62-86: Only computes CW-then-CCW (total_cw_then_ccw)
Missing: CCW-then-CW calculation
What went wrong: Implemented half of reversal strategies
What should be: Both strategies computed per gap
Formula missing: ccw_to_right = 100 - right, cw_from_right_to_left = (100-right) + left, total = sum
Why sloppy: Stopped after first strategy succeeded for User Ex 2
What missed: Other test cases (Test 1) need other strategy
How to prevent: Run ALL tests before declaring done

## ERROR 3: NO EDGE CASE HANDLING
Line 48-89: Missing checks for n=0, sector 0 in array
What went wrong: Directly sorting without filtering
What should be: if (n==0) return 0; filter sector 0 before sort
Test 6 expects: [0] → 0 (head already at 0)
Test 7 expects: [] → 0 (no movement)
Current behavior: Will crash or compute wrong answer
How to prevent: Handle edge cases FIRST before main logic

## ERROR 4: NO DEDUPLICATION
Line 56: std::sort but no std::unique call
Test 11: [5, 5, 95, 95] has duplicates
What should be: After sort, erase duplicates
Formula impact: Duplicate creates artificial "gap" at same value
How to prevent: Always dedupe after sort in array problems
