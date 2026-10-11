// ============================================================================
// CS 110 - Assignment 1: Relief Supply Distribution System
//
// Purpose : Decide how much flood relief to send to each affected area,
//           using a need score, and update the remaining trucks and
//           supply packs after every decision.
//
// Actions (fixed cost of each package):
//   A. Full Relief      = 2 trucks, 50 packs
//   B. Standard Relief  = 1 truck,  30 packs
//   C. Emergency Kit    = 1 truck,  10 packs
//   D. Defer / Monitor  = 0 trucks,  0 packs
//
// Need score (higher = more urgent):
//   Medical need +30 | Damage high +20 / medium +10 / low +5
//   Families / 8     | Damaged route +10 | Flood warning +5
//   Previous aid -10
//
// Score tiers: 66-90 Full, 41-65 Standard, 21-40 Emergency, 0-20 Defer
// ============================================================================

#include <iostream>
#include <string>
using namespace std;

// Input helper functions: each one keeps asking until the answer is valid


// Asks a yes/no question and returns "yes" or "no" 

string getYesNo(string question) {
    string answer;
    cout << question << "(yes / no): " << endl;
    cin >> answer;
    while (answer != "yes" && answer != "no") {
        cout << "Invalid Input! Please type yes or no."<<endl;
        cin >> answer;
    }
    return answer;
}
// Asks for the number of families affected; only 10 to 200 is accepted
int getFamily() {
    int number;
    cout << "Families affected(10-200): " << endl;
    cin >> number;
    while (number > 200 || number < 10) {
        cout << "Invalid Input! Please enter between 10-200."<<endl;
        cin >> number;
    }
    return number;
}

// Asks for the damage level; returns "high", "medium" or "low"
string damageLevel() {
    string level;
    cout << "Damage Level(high,medium,low): " << endl;
    cin >> level;
    while (level != "high" && level != "medium" && level != "low") {
        cout << "Invalid Input! Please enter high, medium or low"<<endl;
        cin >> level;
    }
    return level;
}
// Asks for the route status; returns "open" or "damaged"
string routeAccess() {
    string access;
    cout << "What is the status of route(open/damaged): " << endl;
    cin >> access;
    while (access != "open" && access != "damaged") {
        cout << "Invalid Input! Please enter open / damaged"<<endl;
        cin >> access;
    }
    return access;
}


int main()
{
    // ---------- Variables ----------
    // trucks, aid        : resources still available (never allowed to go below 0)
    // needscore          : score of the request currently being processed
    // successfulcount    : requests that received Full, Standard or Emergency relief
    // deferredcount      : requests deferred because their need was low
    // lowresources       : requests that needed help but stock ran out
    // mode               : 1 = built-in test data (R1-R5), 2 = user enters requests
    int trucks = 3, aid = 70, family = 40, needscore = 0, numberofreq = 0, successfulcount = 0, deferredcount = 0, lowresources = 0, mode;
    string access = "damaged", medical = "yes", received = "yes", damage = "high", flood = "yes", requestName="";

    // ---------- Setup: mode and starting resources ----------
    cout << "1 = use test data(R1 - R5), 2 = enter my own requests : ";
    cin >> mode;
    while (mode != 1 && mode != 2) {
        cout << "Invalid Input. Please Enter 1 or 2."<<endl;
        cin >> mode;

    }
    cout << "Starting Trucks: ";
    cin >> trucks;
    while (trucks < 0) {
        cout << "Invalid Input. Please Enter Valid Number of trucks." << endl;
        cin >> trucks;
    }
    cout << "Starting Supply Packs: ";
    cin >> aid;
    while (aid < 0) {
        cout << "Invalid Input. Please Enter Valid Number of Supply packs." << endl;
        cin >> aid;
    }
    if (mode == 2) {
        cout << "How many requests? ";
        cin >> numberofreq;
        while (numberofreq < 1) {
            cout << "Invalid Input. Please Enter Valid Number of Requests." << endl;
            cin >> numberofreq;
        }
    } 
    else {
        numberofreq = 5;
    }
    // ---------- Main loop: one pass per request ----------
    // Trucks and packs are carried from one request to the next.
    for (int i = 1; i <= numberofreq; i++)
    { 
        // --- Step 1: get the request details ---
        if (mode == 2) {
            // mode 2: read each value from the user (validated by the functions above)
            cout << "\n--- Enter details for request " << i << " ---\n";
            requestName = "Custom request";
            family = getFamily();
            damage = damageLevel();
            medical = getYesNo("Is medical assistance needed? ");
            access = routeAccess();
            flood = getYesNo("Is there flood warning? ");
            received = getYesNo("Did they receive aid before? ");

        }
        // mode 1: the five required test requests
        else if (i == 1)        // R1 Riverside Village
        {
            family = 150; damage = "high"; medical = "yes";
            flood = "yes"; received = "no"; access = "damaged";
            requestName = "Riverside Village";
        }
        else if (i == 2)   // R2 Hilltop Settlement
        {
            family = 60; damage = "medium"; medical = "no";
            flood = "no"; received = "yes"; access = "open";
            requestName = "Hilltop Settlement";
        }
        else if (i == 3)   // R3 Lakeside Camp
        {
            family = 90; damage = "high"; medical = "yes";
            flood = "yes"; received = "no"; access = "open";
            requestName = "Lakeside Camp";
        }
        else if (i == 4)   // R4 Market Town
        {
            family = 200; damage = "low"; medical = "no";
            flood = "no"; received = "no"; access = "open";
            requestName = "Market Town";
        }
        else if (i == 5)   // R5 Bridge Colony
        {
            family = 40; damage = "high"; medical = "yes";
            flood = "yes"; received = "yes"; access = "damaged";
            requestName = "Bridge Colony";
        }
        // --- Step 2: calculate the need score ---
        // Medical need: +30, the largest weight. Medical packs are the most
        // time-critical item, because untreated injuries can be fatal within hours.
        if (medical == "yes")
        {
            needscore += 30;
        }
        // Damaged route: +10. Does not create a need, but the area is cut off
        // and help cannot easily reach it or leave on its own.
        if (access == "damaged")
        {
            needscore += 10;
        }
        // Previous aid: -10. Earlier deliveries partly meet the need, so areas
        // not yet helped are served first.
        if (received == "yes")
        {
            needscore -= 10;

        }
        // Flood warning: +5. Small nudge: more loss may follow, but it is not
        // an emergency today.

        if (flood == "yes")
        {
            needscore += 5;
        }
        // Damage level: high +20, medium +10, low +5. High damage means lost
        // homes, kitchens and stored food, and more injuries.
        if (damage == "high")
        {
            needscore += 20;

        }
        else if (damage == "medium")
        {
            needscore += 10;

        }
        else if (damage == "low")
        {
            needscore += 5;

        }
        // Families affected: families / 8 (about 1 to 25 points). Food need
        // grows with headcount, but this stays below the medical weight so size
        // alone cannot outrank a medical emergency.
        if (family > 0 && family <= 200)
        {
            needscore += family / 8;
        }
        // The score never goes below zero
        if (needscore < 0)
        {
            needscore = 0;
        }
        // --- Step 3: print the request information and its score ---
        cout << "\n-------------------------------\n";
        cout << "Processing request " << i << " - " << requestName <<endl;
        cout << "Calculated NeedScore: " << needscore << endl;
        cout << "Damage Level: " << damage << endl;
        cout << "Families affected: " << family << endl;
        cout << "Medical Need: " << medical << endl;
        cout << "Road access: " << access << endl;
        cout << "Flood Warning: " << flood << endl;
        cout << "Aid Received: " << received << endl;

        // --- Step 4: choose the action from the score, then check resources ---
        // Every package has a fixed cost. A branch only dispatches a package
        // if BOTH trucks and packs cover that cost. If not, it falls back to a
        // smaller package, and finally to Defer, so stock never goes below 0.
 
        // ===== Tier A: score 66-90, Full Relief is recommended =====
        // Every request in this tier has a medical need (without it the
        // highest possible score is 60).
        if (needscore <= 90 && needscore > 65) {
            cout << "Action: Full kit recommended" << endl;
            // Critical score (80+): Full Relief is sent whenever it is affordable,
            // even if this uses up the reserve
            if (needscore >= 80 && trucks >= 2 && aid >= 50)
            {
                cout << "-> Dispatched Full Relief(2 trucks, 50 packs)" << endl;
                trucks -= 2;
                aid -= 50;
                successfulcount += 1;
            }
            // Reserve rule: otherwise Full Relief needs 3 trucks and 80 packs,
            // so at least 1 truck and 30 packs (one Standard Relief) stay in stock
            else if (trucks >= 3 && aid >= 80) {
                cout << "-> Dispatched Full Relief(2 trucks, 50 packs)" << endl;
                trucks -= 2;
                aid -= 50;
                successfulcount += 1;
            }
            // Fallback to Standard Relief: normal reserve (2 trucks, 50 packs),
            // or a damaged-route medical case, which may use the last stock
            else if ((trucks >= 2 && aid >= 50) || (access == "damaged" && trucks >= 1 && aid >= 30)) {
                cout << "->Reduced to Standard Relief(1 truck, 30 packs) -> Reserve kept for later requests" << endl;
                trucks -= 1;
                aid -= 30;
                successfulcount += 1;
            }
            // Fallback to Emergency Kit: a medical case may use the last
            // truck, as long as 1 truck and 10 packs are available
            else if (trucks >= 1 && aid >= 10) {
                cout << "->Reduced to Emergency Relief(1 truck, 10 packs) -> Not enough trucks or packs for Full relief." << endl;
                trucks -= 1;
                aid -= 10;
                successfulcount += 1;
            }
            // Nothing is affordable: defer, and count it as "no resources"
            else {
                cout << "Defer / Monitor (low resources) -> 0 Trucks and 0 packs used" << endl;
                lowresources += 1;
            }
        }
        // ===== Tier B: score 41-65, Standard Relief is recommended =====
        else if (needscore <= 65 && needscore > 40) {
            cout << "Action: Standard kit recommended" << endl;
            // Reserve rule: Standard Relief needs 2 trucks and 50 packs, so
            // at least 1 truck and 20 packs stay in stock for later requests
            if (trucks >= 2 && aid >= 50) {
                cout << "-> Dispatched Standard Relief(1 truck, 30 packs)" << endl;
                trucks -= 1;
                aid -= 30;
                successfulcount += 1;
            }
            // Exception: a damaged-route medical case may use the reserve
            // (1 truck, 30 packs is enough), because it is cut off from other help
            else if (access == "damaged" && medical == "yes" && trucks >= 1 && aid >= 30) {
                cout << "-> Dispatched Standard Relief(1 truck, 30 packs)" << endl;
                trucks -= 1;
                aid -= 30;
                successfulcount += 1;
            }
            // Fallback for a medical case: Emergency Kit if Standard is not available
            else if (trucks >= 1 && aid >= 10 && medical == "yes") {
                cout << "->Reduced to Emergency Relief(1 truck, 10 packs)-> Not enough trucks or packs for Standard relief." << endl;
                trucks -= 1;
                aid -= 10;
                successfulcount += 1;
            }
            // Fallback for a non-medical case: Emergency Kit only if the
            // reserve is kept (more than 1 truck and more than 30 packs)
            else if (trucks > 1 && aid > 30) {
                cout << "->Reduced to Emergency Relief(1 truck, 10 packs) -> Reserve kept for later requests" << endl;
                trucks -= 1;
                aid -= 10;
                successfulcount += 1;
            }
            // Nothing is affordable (or the reserve is protected): defer
            else {
                cout << "Defer / Monitor (low resources) -> 0 Trucks and 0 packs used" << endl;
                lowresources += 1;
            }
        }
        // ===== Tier C: score 21-40, Emergency Kit is recommended =====
        else if (needscore <= 40 && needscore > 20) {
            cout << "Action: Emergency kit recommended" << endl;
            // Non-medical request: allowed only if the reserve stays
            // (more than 1 truck and more than 30 packs)
            if (trucks > 1 && aid > 30) {
                cout << "-> Dispatched Emergency Relief(1 truck, 10 packs)" << endl;
                trucks -= 1;
                aid -= 10;
                successfulcount += 1;
            }
            // Medical request: may use the last truck and the last packs
            else if (trucks >= 1 && aid >= 10 && medical == "yes") {
                cout << "-> Dispatched Emergency Relief(1 truck, 10 packs)" << endl;
                trucks -= 1;
                aid -= 10;
                successfulcount += 1;
            }
            // Otherwise the reserve is kept and the request is deferred
            else {
                cout << "Defer / Monitor (low resources) -> 0 Trucks and 0 packs used" << endl;
                lowresources += 1;
            }
        }
        // ===== Tier D: score 0-20, need is low, so defer / monitor =====
        // (A medical case always scores at least 26, so it never lands here.)
        else if (needscore <= 20 && needscore >= 0) {
            cout << "Defer / Monitor (low score) -> 0 Trucks and 0 packs used" << endl;
            deferredcount += 1;
        }
        // --- Step 5: show the remaining stock after this request ---
        cout << "Remaining Trucks: " << trucks << " | Remaining Supply packs: " << aid << endl;

        needscore = 0;
    }
    // ---------- Final summary ----------
    // successful + deferred + could not be served = total requests
    cout << "\n================================\n";
    cout << "    Final Summary Report    ";
    cout << "\n================================\n";
    cout << "Total Requests Processed: "<<numberofreq<<endl;
    cout << "Successfully handled: " << successfulcount << endl;
    cout << "Deferred(low need): " << deferredcount << endl;
    cout << "Could not be served(no resources): " << lowresources << endl;
    cout << "Final Remaining Trucks: " << trucks << endl;
    cout << "Final Remaining Supply packs: " << aid << endl;
    cout << "\n================================\n";

}