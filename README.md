# Relief Supply Distribution System

## Overview
This C++ Program helps to decide how to distribute relief supplies to areas affected by a disaster. It gives each request a need score based on the damage level, number of families affected, medical needs, road acccess, flood warnings and whether the area has already recieved aid.

The program can run five built-in test requests or accept custom requests from the user.

## 1. Need Score Calculation
The score is initialized with a value of 0. Points are then added or subtracted as follows:

| Factor | Change in Score |
| --- | ---: |
| Medical Assistance Needed | +30 |
| Route Damaged | +10 |
| High Damage | +20 |
| Medium Damage | +10 |
| Low Damage | +5 |
| Flood Warning Present | +5 |
| Families Affected | `number of families / 8` |
| Aid Recieved Previously | -10 |

Family score calculation uses integer division, so anything after the decimal point is neglected. If the final score is below zero, the program sets it to zero.

## Decision and Action Rules
The program first decides the recommended action, based on the need score, as follows:

| Need Score | Initial Recommendation |
| --- | ---: |
| 66-90 | Full Relief |
| 41-65 | Standard Relief |
| 21-40 | Emergency Kit |
| 0-20 | Defer/Monitor |

After that, the program checks the inventory and, for some cases other conditions such as medical aid needed or damaged road access. If the initial recommendation could not be dispatched, it may downgrade to a lower relief level. And if no applicable dispatch condition is fulfilled, the request is deferred.

| Relief Dispatched | Trucks Used | Supply Packs Used |
| --- | --- | ---: |
| Full Relief | 2 | 50 |
| Standard Relief | 1 | 30 |
| Emergency Relief | 1 | 10 |
| Defer/Monitor | 0 | 0 |

After each request, the program updates the inventory before processing the next request. At the end, it displays the total number of requests handled, deferred due to low score or not handled due to lack of resources.

## 3. Why Such Rules Were Set
The score calculation system is designed to give higher priority to areas facing more urgent conditions. Medical Assistance recieves the highest priority because urgent health needs require quick attention. High Infrastructure damage, damaged roads and flood warnings also increase urgency. The number of families affected also contribute to the score so that larger affected population are given priority. Whereas, previous aid reduces urgency in order to facilitate those areas which have recieved no aid yet.

The score ranges separate requests into different levels of response, whereas the inventory checks prevent the program from dispatching more trucks or supply packs than currently available. The option to downgrade to a lower level of response is also present so that affected areas can recieve a smaller amount of relief when full response is not possible.

## Test Results
The built-in test data was traced using Mode 1, with 5 starting trucks and 120 starting supply packs. The results are as shown below:

| Test Request | Need Score | Action Taken | Remaining Trucks | Remaining Supply Packs |
| --- | --- | --- | --- | ---: |
| R1- Riverside Village | 83 | Full Relief (2 trucks, 50 supply packs) | 3 | 70 |
| R2- Hilltop Settlement | 7 | Defer/Monitor (low score) | 3 | 70 |
| R3- Lakeside Camp | 66 | Standard Relief (1 trucks, 30 supply packs) | 2 | 40 |
| R4- Market Town | 30 | Emergency Relief (1 trucks, 10 supply packs) | 1 | 30 |
| R5- Bridge Colony | 60 | Standard Relief (2 trucks, 50 supply packs) | 0 | 0 |

### Final Summary for this test:
- **Total Requets Processed:** 5
- **Successfully Handled:** 4
- **Deferred(due to low score):** 1
- **Deferred(due to lack of resources):** 0
- **Remaining Trucks:** 0
- **Remaining Supply Packs:** 0

## GitHub Repository
Repository Link: 

## Group Members and Contribution

| Group Member | Contribution |
| --- | ---: |
| Muhammad Mustafa Asim | README.md and Repository Creation |
| Uzair Hassan Farooq | Code |
| Muhammad Daud | Flowchart |

## How to Compile and Run
Use a C++ Compiler to compile the program and then run the executable file.

## Use of AI
AI assisstance was used to explain the main idea and logic of the assignment, and in the formatting of comments in the code file.