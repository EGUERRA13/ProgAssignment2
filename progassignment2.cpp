#include <iostream>
#include <math.h> 
using namespace std;

struct event {
  int type;
  float time;
  event* nextEvent;
  event(int type1, double time1){
    type = type1;
    time = time1;
  }
};

void schedule_event(int type, double t, event* eq_head) {
	event* e = new event(type, t);
	if (eq_head != NULL){
    eq_head = e;
  }else {
  eq_head->nextEvent = e;
  }
}

void arr_handler(event* e, double clock, bool serverIdle, double arrival_rate, int readyQueueCount) {
  srand(time(NULL));
  double UniformDistribution = (double) rand()/ RAND_MAX;
  double ServiceTime = (-25)*log(UniformDistribution);
  double InterArrivalTime2 = (-1/arrival_rate)*log(UniformDistribution);
	if (serverIdle == true) {
		serverIdle = false;
		schedule_event(1,clock+ServiceTime,e);
	}else{
		readyQueueCount++;
  }
	schedule_event(0,clock+InterArrivalTime2,e);
}

void dep_handler(event* e, double clock, bool serverIdle, double arrival_rate, int readyQueueCount) {
  srand(time(NULL));
  double UniformDistribution = (double) rand()/ RAND_MAX;
  double ServiceTime = (-25)*log(UniformDistribution);
	if (readyQueueCount == 0){
    serverIdle = true;
  }
	else {
		readyQueueCount--;
		schedule_event(1,clock+ServiceTime,e);
	}
}

void simulation(double arrival_rate, double service_time){
  srand(time(NULL));
  double UniformDistribution = (double) rand()/ RAND_MAX;
  double InterArrivalTime1 = (-1/arrival_rate)*log(UniformDistribution);
  double clock = 0;
	bool serverIdle = true;
	int readyQueueCount = 0;
	event* eq_head = NULL; // event queue head
	double t = clock + InterArrivalTime1;
	schedule_event (0, t, eq_head);
  int arrCount = 0;
  int depCount = 0;

  double temp_ready_count = 0;
  double temp_busy = 0;
	while ( depCount != 10000 ) {
    double old_clock = clock;
	  event* e = eq_head;
	  clock = e->time;
    double duration = clock - old_clock;
    if (!serverIdle){
      temp_busy += duration;
    }
    temp_ready_count = (readyQueueCount * duration)+temp_ready_count ;

    
	  switch (e->type) {
		  case 0:
        arrCount++;
			  arr_handler(e,clock, serverIdle, arrival_rate,readyQueueCount); break;
		  case 1:
        depCount++;
			  dep_handler(e,clock, serverIdle, arrival_rate,readyQueueCount); break;
		}
	  eq_head = e->nextEvent;
	}
  
  double AvgTurnAroundTime = temp_busy / 10000;
  double TotalThroughput = 10000 / clock;
  double CPUutilization = temp_busy / clock;
  double avgNumProcesses = temp_ready_count / clock;
  cout << "Average Turnaround Time of Processes: " << AvgTurnAroundTime << endl;
  cout << "Total Throughput: " << TotalThroughput << endl;
  cout << "Average CPU Utilization: " << CPUutilization << endl;
  cout << "Average number of processes in Ready Queue: " << avgNumProcesses << endl;

}

int main() {

  simulation(10,.04);
  simulation(11,.04);
  simulation(12,.04);
  simulation(13,.04);
  simulation(14,.04);
  simulation(15,.04);
  simulation(16,.04);
  simulation(17,.04);
  simulation(18,.04);
  simulation(19,.04);
  simulation(20,.04);
  simulation(21,.04);
  simulation(22,.04);
  simulation(23,.04);
  simulation(24,.04);
  simulation(25,.04);
  simulation(26,.04);
  simulation(27,.04);
  simulation(28,.04);
  simulation(29,.04);
  simulation(30,.04);

} 