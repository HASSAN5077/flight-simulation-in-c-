#include<iostream>
using namespace std;
// class for flight details 
class Flight {
public:
	int flightId, fuel, waitingTime, runwayId;
	string destination , depatureCity;
public:

};
// inherited class for arrival flight
class Arrival : public Flight {
public:
	string arrivalDate, arrivalTime, landTime;
};
// inherited class for departure flight
class Departure : public Flight {
public:
	string departureDate, departureTime, takeoffTime;
};
// class for managing runways 
class Runways {
public:
	int ArrivalQueue1[30];
	int ArrivalQueue2[30];
	int DepQueue1[30];
	int DepQueue2[30];
	int Stack[30];
	int top = 0;
	int totalEmergencyLandings = 0;
	int aTail1 = 0, aTail2 = 0, depTail1 = 0, depTail2 = 0, aCounter1 = 0, aCounter2 = 0, dCounter1 = 0, dCounter2 = 0;
public:
	bool isFull() {				//isfull method
		if (aCounter1 >= 30 || aCounter2 >= 30)
			return true;
		if (dCounter1 >= 30 || dCounter2 >= 30)
			return true;

		return false;
	}
	bool isEmpty() {				//isempty Method
		if (aCounter1 <= 30 || aCounter2 <= 30)
			return true;
		if (dCounter1 <= 30 || dCounter2 <= 30)
			return true;
		return false;
	}
	// function for managing arrival flights landings 
	bool addArrivalQueue(int num) {
		if (isFull())
			return false;
		if (aTail1 > aTail2) {
			if (aTail2 == 30)
				aTail2 = 0;
			ArrivalQueue2[aTail2++] = num;
			aCounter2++;
			if (aTail2 == 1)
				cout << "\nAssigning departure runway 2";
			else
				cout << "\nRunway is busy Please Wait. Queue number is " << aCounter2;
		}
		else {
			if (aTail1 == 30)
				aTail1 = 0;
			ArrivalQueue1[aTail1++] = num;
			aCounter1++;
			if (aTail1 == 1)
				cout << "\nAssigning departure runway 1";
			else
				cout << "\nRunway is busy Please Wait. Queue number is " << aCounter1;
		}
		return true;
	}
	// function to manage the departure runways 
	bool addDepartuerQueue(int num) {
		if (depTail1 > depTail2) {
			if (depTail2 == 30)
				depTail2 = 0;
			DepQueue2[depTail2++] = num;
			dCounter2++;
			if (depTail2 == 1)
				cout << "\nAssigning arrival runway 2";
			else
				cout << "\nRunway is busy Please Wait. Queue number is " << dCounter2;
		}
		else {
			if (depTail1 == 30)
				depTail1 = 0;
			DepQueue1[depTail1++] = num;
			dCounter1++;
			if (depTail1 == 1)
				cout << "\nAssigning arrival runway 1";
			else
				cout << "\nRunway is busy Please Wait.  Queue number is " << dCounter1;
		}
		return true;
	}
	bool emergencyPriority(int flightId) {						//EmergencyLanding using Prority Queue
		for (int i = 0; i < aCounter1; i++) {
			if (ArrivalQueue1[i] == flightId)
			{
				if (aCounter1 >= 30)
					return false;
				top = 0;
				aTail1--;
				while (ArrivalQueue1[aTail1] != flightId) {
					Stack[top++] = ArrivalQueue1[aTail1--];
				}
				--top;
				while (top >= 0) {
					ArrivalQueue1[aTail1++] = Stack[top--];
				}
				cout << "\nAssigning Runway 1 on emergency basis";
				aCounter1--;
				totalEmergencyLandings++;
				return true;
			}
		}
		for (int i = 0; i < aCounter2; i++) {
			if (ArrivalQueue2[i] == flightId)
			{
				if (aCounter1 >= 30)
					return false;
				top = 0;
				aTail2--;
				while (ArrivalQueue2[aTail2] != flightId) {
					Stack[top++] = ArrivalQueue2[aTail2--];
				}
				--top;
				while (top >= 0) {
					ArrivalQueue2[aTail2++] = Stack[top--];
				}
				cout << "\nAssigning Runway 2 on emergency basis";
				aCounter2--;
				totalEmergencyLandings++;
				return true;
			}
		}
		return false;
	}
};
int main() {
	Arrival arrival;
	Departure dep;
	Runways runway;
	int totalArrivalWaitingTime = 0, totalTakeoffTime = 0, wcounter = 0, tcounter = 0;
	int option = 0;
	while (option != -1) {
		cout << "\n\n1: Arrival " << endl;;
		cout << "2: Departure " << endl;
		cout << "3: Emergency" << endl;
		cout << "4: Reports" << endl;
		cout << "-1: EXIT System" << endl;
		cout << "Enter Option: ";
		cin >> option;
		switch (option) {
		case 1:

			cout << "Enter Flight id: ";
			cin >> arrival.flightId;
			cout << "Enter fuel in barrel: ";
			cin >> arrival.fuel;
			cout << "Enter Waiting Time in minutes:";
			cin >> arrival.waitingTime;
			totalArrivalWaitingTime = totalArrivalWaitingTime + arrival.waitingTime;
			wcounter++;
			cout << "Enter Departure City: ";
			cin >> arrival.depatureCity;
			cout << "Enter Destination: ";
			cin >> arrival.destination;
			cout << "Enter Arrival Date ";
			cin >> arrival.arrivalDate;
			cout << "Enter Arrival Time ";
			cin >> arrival.arrivalTime;
			cout << "Enter Landing Time ";
			cin >> arrival.landTime;
			runway.addArrivalQueue(arrival.flightId); //adding in queue
			break;
		/*Departure Case */  case 2:
			cout << "Enter Flight id: ";
			cin >> dep.flightId;
			cout << "Enter fuel in barrel: ";
			cin >> dep.fuel;
			cout << "Enter Waiting Time in minutes :";
			cin >> dep.waitingTime;
			totalTakeoffTime = totalTakeoffTime + dep.waitingTime;
			tcounter++;
			cout << "Enter Departure City: ";
			cin >> arrival.depatureCity;
			cout << "Enter Destination: ";
			cin >> dep.destination;
			cout << "Enter Departure Date: ";
			cin >> dep.departureDate;
			cout << "Enter Departure Time ;";
			cin >> dep.departureTime;
			cout << "Enter Landing Time :";
			cin >> dep.takeoffTime;
			runway.addDepartuerQueue(dep.flightId);  //adding in queue
			break;
		case 3:
			cout << "Enter Flight id for emergency landing: ";
			int flightId;
			cin >> flightId;
			if (runway.emergencyPriority(flightId))
				cout << "Flight" << flightId << "Landed Successfully\n", flightId;
			else
				cout << "\n\n---------- Id not found -----------";
			break;
		case 4:
			cout << "\n-------------- Reports --------------" << "\n\n";
			if (wcounter == 0) {
				cout << "\nAverage Landing Waiting Time: " << "0 minutes";
			}
			else {
				cout << "\nAverage Landing Waiting Time: " << totalArrivalWaitingTime / wcounter << " minutes";
			}
			if (tcounter == 0) {
				cout << "\nAverage TakeOff Waiting Time: " << "0 minutes";
			}
			else {
				cout << "\nAverage TakeOff Waiting Time: " << totalTakeoffTime / tcounter << " minutes";
			}

			cout << "\nTotal landings: " << runway.aCounter1 + runway.aCounter2;
			cout << "\nTotal departed flights: " << runway.dCounter1 + runway.dCounter2;
			cout << "\nTotal emergeny landings: " << runway.totalEmergencyLandings << endl;
			break;
		case -1:
			continue;
		default:
			cout << "\nInvalid input. Enter again" << endl;
		}
	}
}