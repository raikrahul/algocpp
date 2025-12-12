01.. INPUT: d[]={5,3,4,2}, n=5, M=7 → d=distances array, n=station count, M=tank capacity → GIVEN: 4 values in d[], 5 stations s₁..s₅, tank holds 7 → AXIOMATIC: d[] has n-1=5-1=4 elements ✓ | What: d[i]=distance s_i→s_{i+1} | Why: car travels between stations | Where: d[0]=5 means s₁→s₂=5 miles | Who: driver at s₁ with tank=M=7 | When: before each leg, check tank | Without: tank<d[i] → stuck | Which: refuel when tank<d[i]

02.. POSITIONS: s₁=0, s₂=0+d[0]=0+5=5, s₃=5+d[1]=5+3=8, s₄=8+d[2]=8+4=12, s₅=12+d[3]=12+2=14 → cumulative sum of d[] → AXIOMATIC: position[i]=position[i-1]+d[i-1] → s₅ at mile 14 from s₁ ✓ | VERIFY: 5+3+4+2=14 ✓

03.. TANK DEPLETION: start tank=M=7 → drive d[0]=5 → tank=7-5=2 → AXIOMATIC: tank_after = tank_before - d[i] → 7-5=2 ✓ | F1: you will forget subtraction happens DURING travel not AT station

04.. DECISION AT s₂: tank=2, next leg d[1]=3 → compare: 2<3? → 2<3=✓ → tank<d[1] → must refuel → AXIOMATIC: if tank<d[i] then refuel else drive → 2<3 ∴ refuel ✓

05.. REFUEL: tank=2 → refuel → tank=M=7 → stops=0+1=1 → AXIOMATIC: refuel sets tank=M, increments stops by 1 → tank:2→7, stops:0→1 ✓

06.. DRIVE AFTER REFUEL: tank=7 → drive d[1]=3 → tank=7-3=4 → AXIOMATIC: always subtract d[i] after check (refuel or not) → 7-3=4 ✓

07.. AT s₃: tank=4, next leg d[2]=4 → compare: 4<4? → 4<4=✗ → tank≥d[2] → no refuel → AXIOMATIC: 4≥4 ∴ skip refuel → stops=1 unchanged ✓

08.. DRIVE FROM s₃: tank=4 → drive d[2]=4 → tank=4-4=0 → AXIOMATIC: 4-4=0 → tank can be 0 after leg ✓

09.. AT s₄: tank=0, next leg d[3]=2 → compare: 0<2? → 0<2=✓ → must refuel → tank=M=7, stops=1+1=2 → AXIOMATIC: 0<2 ∴ refuel → stops:1→2 ✓

10.. DRIVE FROM s₄: tank=7 → drive d[3]=2 → tank=7-2=5 → ARRIVED at s₅ → stops=2 → AXIOMATIC: loop ends after n-1=4 legs ✓

11.. ALGORITHM: tank=M, stops=0 → for i=0 to n-2: if(tank<d[i]) {tank=M; stops++;} tank-=d[i]; → return stops → AXIOMATIC: derived from steps 03-10 ✓

12.. TRACE TABLE:
|i|station|tank_before|d[i]|tank<d[i]?|action|tank_after|stops|
|0|s₂|7|5|7<5=✗|drive|7-5=2|0|
|1|s₃|2|3|2<3=✓|refuel→7,drive|7-3=4|1|
|2|s₄|4|4|4<4=✗|drive|4-4=0|1|
|3|s₅|0|2|0<2=✓|refuel→7,drive|7-2=5|2|
∴ stops=2 ✓

13.. EDGE n=2: d[]={6}, M=7 → tank=7 → 7<6=✗ → tank=7-6=1 → ARRIVED → stops=0 → AXIOMATIC: single leg, no refuel needed ✓

14.. EDGE n=2: d[]={7}, M=7 → tank=7 → 7<7=✗ → tank=7-7=0 → ARRIVED → stops=0 → AXIOMATIC: exactly empty on arrival, valid ✓

15.. HARD: d[]={3,5,6,2,8,1}, n=7, M=10 → i=0: tank=10, 10<3=✗, tank=10-3=7, stops=0 → i=1: 7<5=✗, tank=7-5=2, stops=0 → i=2: 2<6=✓, tank=10, stops=1, tank=10-6=4 → i=3: 4<2=✗, tank=4-2=2, stops=1 → i=4: 2<8=✓, tank=10, stops=2, tank=10-8=2 → i=5: 2<1=✗, tank=2-1=1 → ARRIVED → stops=2 ✓

16.. HARD: d[]={4,4,4,4}, n=5, M=5 → i=0: 5<4=✗, tank=5-4=1 → i=1: 1<4=✓, tank=5, stops=1, tank=5-4=1 → i=2: 1<4=✓, tank=5, stops=2, tank=5-4=1 → i=3: 1<4=✓, tank=5, stops=3, tank=5-4=1 → ARRIVED → stops=3 ✓

17.. HARD: d[]={7,7,7}, n=4, M=7 → i=0: 7<7=✗, tank=7-7=0 → i=1: 0<7=✓, tank=7, stops=1, tank=7-7=0 → i=2: 0<7=✓, tank=7, stops=2, tank=7-7=0 → ARRIVED → stops=2 ✓

18.. HARD: d[]={1,1,1,1,1,1,1}, n=8, M=7 → i=0: 7-1=6 → i=1: 6-1=5 → i=2: 5-1=4 → i=3: 4-1=3 → i=4: 3-1=2 → i=5: 2-1=1 → i=6: 1<1=✗, 1-1=0 → ARRIVED → stops=0 → AXIOMATIC: 7≥sum(d)=7 ∴ no refuel ✓

19.. STRESS: n=1000, d[i]=1 ∀i, M=1000 → tank=1000 → 999 legs → tank=1000-999=1 → stops=0 → AXIOMATIC: sum(d)=999<M=1000 ∴ stops=0 ✓

20.. STRESS: n=1000, d[i]=1000 ∀i, M=1000 → i=0: 1000-1000=0 → i=1: 0<1000=✓, refuel, 1000-1000=0, stops=1 → pattern: refuel at every station except first → stops=998 ✓

21.. F1: forget tank-=d[i] during travel → tank=7, drive 5 → tank should be 2 not 7 → TRAP

22.. F2: check tank<d[i] AFTER drive → WRONG → check BEFORE drive → at s₂, tank=2, check 2<3 BEFORE leaving s₂ ✓

23.. F3: confuse d[i] meaning → d[i]=distance TO station i+1 FROM station i → d[0]=5 means s₁→s₂=5, NOT s₂→s₃

24.. F4: refuel AFTER subtract → WRONG ORDER → if(tank<d[i]) {tank=M; stops++;} THEN tank-=d[i]

25.. F5: loop i=1 to n → WRONG → loop i=0 to n-2 (0-indexed) → n-1 legs for n stations

26.. F6: count refuel at destination → WRONG → no refuel needed after arrival → loop ends at i=n-2

27.. F7: initialize tank=0 → WRONG → start at s₁ with FULL tank → tank=M

28.. CODE: int FindMinStops(int d[], int n, int m) { int tank=m, stops=0; for(int i=0; i<n-1; i++) { if(tank<d[i]) {tank=m; stops++;} tank-=d[i]; } return stops; }

29.. COMPLEXITY: O(n) time → single loop n-1 iterations → O(1) space → 3 integers: tank, stops, i

30.. GREEDY PROOF: delay refuel at sᵢ → run empty before sⱼ → stuck → ∴ refuel at first tank<d[i] is optimal → no backtracking possible

═══════════════════════════════════════════════════════════════════════════════
USER MISTAKES LOG
═══════════════════════════════════════════════════════════════════════════════

M1.. LINE 45: d[i+1] - d[i] → WRONG → d[i] → d[] is distances not positions → d[0]=5 not d[1]-d[0]=3-5=-2 → SLOPPY: confused cumulative positions with raw distances → PREVENT: d[] given as distances, no subtraction needed

M2.. LINE 47: stops++ → missing semicolon → stops++; → SLOPPY: rushed typing → PREVENT: compile before moving on

M3.. LINE 51: retrun → typo → return → SLOPPY: did not read error messages → PREVENT: eyes on screen not keyboard

M4.. VERBAL: "d[0] is 0" → d[0]=5 → misread array d[]={5,3,4,2} → SLOPPY: glanced at index, typed index value instead of array value → PREVENT: finger on array element, read aloud

M5.. VERBAL: "station 1 to station 2 is 4 units" → s₁→s₂=d[0]=5 → SLOPPY: mixed up d[2]=4 with d[0]=5 → PREVENT: trace with finger left to right

M6.. VERBAL: "station 0" → stations are s₁..s₅ (1-indexed in problem) → SLOPPY: mixed 0-indexed code with 1-indexed problem → PREVENT: use s₁ notation in traces

M7.. VERBAL: "leg 4 cost" → only legs 0,1,2,3 exist (4 legs for 5 stations) → SLOPPY: counted stations as legs → PREVENT: n stations = n-1 legs

M8.. VERBAL: "distance between leg 0 and leg 1" → d[0] is length OF leg 0, not between legs → SLOPPY: leg=segment, station=point → PREVENT: legs have LENGTH, stations have POSITION

M9.. STEP 02: introduced "position" variable → NOT NEEDED → algorithm uses tank,d[i],M only → JUMPED AHEAD → PREVENT: only introduce variables used in final code
