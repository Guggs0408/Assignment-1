
#include <iostream>
#include <string>
using namespace std;
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
    int trucks = 3, aid = 70, family = 40, needscore = 0, numberofreq = 0, successfulcount = 0, deferredcount = 0, lowresources = 0, mode;
    string access = "damaged", medical = "yes", received = "yes", damage = "high", flood = "yes", requestName="";

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
    for (int i = 1; i <= numberofreq; i++)
    { 
        if (mode == 2) {
            cout << "\n--- Enter details for request " << i << " ---\n";
            requestName = "Custom request";
            family = getFamily();
            damage = damageLevel();
            medical = getYesNo("Is medical assistance needed? ");
            access = routeAccess();
            flood = getYesNo("Is there flood warning? ");
            received = getYesNo("Did they receive aid before? ");

        }
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
        if (medical == "yes")
        {
            needscore += 30;
        }

        if (access == "damaged")
        {
            needscore += 10;
        }

        if (received == "yes")
        {
            needscore -= 10;

        }

        if (flood == "yes")
        {
            needscore += 5;
        }

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

        if (family > 0 && family <= 200)
        {
            needscore += family / 8;
        }
        if (needscore < 0)
        {
            needscore = 0;
        }
        cout << "\n-------------------------------\n";
        cout << "Processing request " << i << " - " << requestName <<endl;
        cout << "Calculated NeedScore: " << needscore << endl;
        cout << "Damage Level: " << damage << endl;
        cout << "Families affected: " << family << endl;
        cout << "Medical Need: " << medical << endl;
        cout << "Road access: " << access << endl;
        cout << "Flood Warning: " << flood << endl;
        cout << "Aid Received: " << received << endl;

        if (needscore <= 90 && needscore > 65) {
            cout << "Action: Full kit recommended" << endl;
            if (needscore >= 80 && trucks >= 2 && aid >= 50)
            {
                cout << "-> Dispatched Full Relief(2 trucks, 50 packs)" << endl;
                trucks -= 2;
                aid -= 50;
                successfulcount += 1;
            }
            else if (trucks >= 3 && aid >= 80) {
                cout << "-> Dispatched Full Relief(2 trucks, 50 packs)" << endl;
                trucks -= 2;
                aid -= 50;
                successfulcount += 1;
            }
            else if ((trucks >= 2 && aid >= 50) || (access == "damaged" && trucks >= 1 && aid >= 30)) {
                cout << "->Reduced to Standard Relief(1 truck, 30 packs) -> Reserve kept for later requests" << endl;
                trucks -= 1;
                aid -= 30;
                successfulcount += 1;
            }
            else if (trucks >= 1 && aid >= 10) {
                cout << "->Reduced to Emergency Relief(1 truck, 10 packs) -> Not enough trucks or packs for Full relief." << endl;
                trucks -= 1;
                aid -= 10;
                successfulcount += 1;
            }
            else {
                cout << "Defer / Monitor (low resources) -> 0 Trucks and 0 packs used" << endl;
                lowresources += 1;
            }
        }
        else if (needscore <= 65 && needscore > 40) {
            cout << "Action: Standard kit recommended" << endl;
            if (trucks >= 2 && aid >= 50) {
                cout << "-> Dispatched Standard Relief(1 truck, 30 packs)" << endl;
                trucks -= 1;
                aid -= 30;
                successfulcount += 1;
            }
            else if (access == "damaged" && medical == "yes" && trucks >= 1 && aid >= 30) {
                cout << "-> Dispatched Standard Relief(1 truck, 30 packs)" << endl;
                trucks -= 1;
                aid -= 30;
                successfulcount += 1;
            }
            else if (trucks >= 1 && aid >= 10 && medical == "yes") {
                cout << "->Reduced to Emergency Relief(1 truck, 10 packs)-> Not enough trucks or packs for Standard relief." << endl;
                trucks -= 1;
                aid -= 10;
                successfulcount += 1;
            }
            else if (trucks > 1 && aid > 30) {
                cout << "->Reduced to Emergency Relief(1 truck, 10 packs) -> Reserve kept for later requests" << endl;
                trucks -= 1;
                aid -= 10;
                successfulcount += 1;
            }
            else {
                cout << "Defer / Monitor (low resources) -> 0 Trucks and 0 packs used" << endl;
                lowresources += 1;
            }
        }

        else if (needscore <= 40 && needscore > 20) {
            cout << "Action: Emergency kit recommended" << endl;
            if (trucks > 1 && aid > 30) {
                cout << "-> Dispatched Emergency Relief(1 truck, 10 packs)" << endl;
                trucks -= 1;
                aid -= 10;
                successfulcount += 1;
            }
            else if (trucks >= 1 && aid >= 10 && medical == "yes") {
                cout << "-> Dispatched Emergency Relief(1 truck, 10 packs)" << endl;
                trucks -= 1;
                aid -= 10;
                successfulcount += 1;
            }
            else {
                cout << "Defer / Monitor (low resources) -> 0 Trucks and 0 packs used" << endl;
                lowresources += 1;
            }
        }
        else if (needscore <= 20 && needscore >= 0) {
            cout << "Defer / Monitor (low score) -> 0 Trucks and 0 packs used" << endl;
            deferredcount += 1;
        }

        cout << "Remaining Trucks: " << trucks << " | Remaining Supply packs: " << aid << endl;

        needscore = 0;
    }
    
    
    
        
        
    
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

