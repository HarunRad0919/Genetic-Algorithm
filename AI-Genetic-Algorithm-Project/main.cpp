#include <iostream>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

#define POPULATION_SIZE 500

struct activities{
  string className;
  int enrollment;
  vector<string> prefFac;
  vector<string> otherFac;
};

struct rooms{
  string roomName;
  int roomSize;
};

struct period{
  string facilitator;
  string time;
  activities act;
  rooms room;
  float fitness;
  bool ranFac = false;
  int actCount = 0;
};

struct schedule{
  vector<period> periods;
  float totalFitness = 0;
};

vector<schedule> scheduleGen(string facilitators[10], string times[6], vector<activities> acts, vector<rooms> room){
  srand(time(0));
  vector<schedule> population;
  vector<period> tempSchedule;
  schedule tempPop;
  period tempPeriod;
  string tempFac;
  string tempTime;
  activities tempAct; 
  rooms tempRooms;
  for (int i = 0; i < POPULATION_SIZE; i++){
    tempSchedule.clear();
    for (int j = 0; j < 6; j++){
      int randomNum = rand() % 10;
      tempFac = facilitators[randomNum];
      tempTime = times[j];
      randomNum = rand() % (acts.size()-1);
      tempAct = acts.at(randomNum);
      randomNum = rand() % (room.size()-1);
      tempRooms = room.at(randomNum);
      tempPeriod = {tempFac, tempTime, tempAct, tempRooms};
      tempSchedule.push_back(tempPeriod);
      tempPop.periods = tempSchedule;
    }
    population.push_back(tempPop);
  }
  cout << population.size() << endl;
  cout << population.at(150).periods.size();
  for (int i = 0; i < 1; i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      cout << "Population: " << i << endl;
      cout << "Room size: " << population.at(i).periods.at(j).room.roomSize << endl;
      cout << "Enrollment: " << population.at(i).periods.at(j).act.enrollment << endl;
      cout << "Faciltator: " << population.at(i).periods.at(j).facilitator << endl;
      cout << "Activity: " << population.at(i).periods.at(j).act.className << endl;
      cout << "Room : " << population.at(i).periods.at(j).room.roomName << endl;
      cout << "First Fitness: " << population.at(i).periods.at(j).fitness << endl;
      cout << endl;
    }
  }
  return population;
}

void checkRoom(vector<schedule> &population){
  for (int i = 0; i < population.size(); i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      if (population.at(i).periods.at(j).room.roomSize < population.at(i).periods.at(j).act.enrollment){
        population.at(i).periods.at(j).fitness -= .5;
      }
      if (population.at(i).periods.at(j).room.roomSize > (population.at(i).periods.at(j).act.enrollment*3)){
        population.at(i).periods.at(j).fitness -= .2;
      }
      if (population.at(i).periods.at(j).room.roomSize > (population.at(i).periods.at(j).act.enrollment*6)){
        population.at(i).periods.at(j).fitness -= .4;
      }
      if (population.at(i).periods.at(j).room.roomSize >= population.at(i).periods.at(j).act.enrollment && population.at(i).periods.at(j).room.roomSize < (population.at(i).periods.at(j).act.enrollment*3) && population.at(i).periods.at(j).room.roomSize < (population.at(i).periods.at(j).act.enrollment*6)){
        population.at(i).periods.at(j).fitness += .3;
      }
    }
  }
  for (int i = 0; i < 1; i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      cout << "Population: " << i << endl;
      cout << "After class Fitness: " << population.at(i).periods.at(j).fitness << endl;
      cout << endl;
    }
  }
}

void checkActivity(vector<schedule> &population){
  for (int i = 0; i < population.size(); i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      for (int k = 0; k < population.at(i).periods.at(j).act.prefFac.size(); k++){
        if (population.at(i).periods.at(j).facilitator == population.at(i).periods.at(j).act.prefFac.at(k)){
          population.at(i).periods.at(j).fitness += .5;
          population.at(i).periods.at(j).ranFac = true;
        }
      }
    }
  }
  for (int i = 0; i < population.size(); i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      for (int k = 0; k < population.at(i).periods.at(j).act.otherFac.size(); k++){
        if (population.at(i).periods.at(j).facilitator == population.at(i).periods.at(j).act.otherFac.at(k)){
          population.at(i).periods.at(j).fitness += .2;
          population.at(i).periods.at(j).ranFac = true;
        }
      }
    }
  }
  for (int i = 0; i < population.size(); i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      if (population.at(i).periods.at(j).ranFac == false){
        population.at(i).periods.at(j).fitness -= .1;
      }
    }
  }
  for (int i = 0; i < 1; i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      cout << "Population: " << i << endl;
      cout << "After activity Fitness: " << population.at(i).periods.at(j).fitness << endl;
      cout << endl;
    }
  }
}

void checkFacilitator(vector<schedule> &population){
  for (int i = 0; i < population.size(); i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      for (int k = 0; k < population.at(i).periods.size(); k++){
        if (population.at(i).periods.at(j).facilitator == population.at(i).periods.at(k).facilitator){
          population.at(i).periods.at(j).actCount++;
        }
      }
    }
  }
  for (int i = 0; i < population.size(); i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      if (population.at(i).periods.at(j).actCount > 4){
        population.at(i).periods.at(j).fitness -= .5;
      }
      if (population.at(i).periods.at(j).actCount == 1 || population.at(i).periods.at(j).actCount == 2){
        population.at(i).periods.at(j).fitness -= .4;
      }
    }
  }
  int tempk = 1;
  for (int i = 0; i < population.size(); i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      if (tempk < population.at(i).periods.size()-1){
        if (population.at(i).periods.at(j).facilitator == population.at(i).periods.at(tempk).facilitator){
          population.at(i).periods.at(j).fitness += .5;
        }
      }
      tempk++;
    }
  }
  for (int i = 0; i < 1; i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      cout << "Population: " << i << endl;
      cout << "After Facilitator Fitness: " << population.at(i).periods.at(j).fitness << endl;
      cout << endl;
    }
  }
}

void checkSpecific(vector<schedule> &population){
  int tempk = 4;
  int templ = 1;
  int tempm = 2;
  for (int i = 0; i < population.size(); i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      if (tempk < population.at(i).periods.size()){
        if (population.at(i).periods.at(j).act.className == "SLA100A" && population.at(i).periods.at(tempk).act.className == "SLA100B"){
          population.at(i).periods.at(j).fitness += .5;
        }
        if (population.at(i).periods.at(j).act.className == "SLA100B" && population.at(i).periods.at(tempk).act.className == "SLA100A"){
          population.at(i).periods.at(j).fitness += .5;
        }
        if (population.at(i).periods.at(j).act.className == "SLA191A" && population.at(i).periods.at(tempk).act.className == "SLA191B"){
          population.at(i).periods.at(j).fitness += .5;
        }
        if (population.at(i).periods.at(j).act.className == "SLA191B" && population.at(i).periods.at(tempk).act.className == "SLA191A"){
          population.at(i).periods.at(j).fitness += .5;
        }
      }
      tempk++;
      if (templ < population.at(i).periods.size()){
        if ((population.at(i).periods.at(j).act.className == "SLA100A" || population.at(i).periods.at(j).act.className == "SLA100B") && (population.at(i).periods.at(templ).act.className == "SLA191A" || population.at(i).periods.at(templ).act.className == "SLA191B")){
          if ((population.at(i).periods.at(j).room.roomName == "Roman 201" && population.at(i).periods.at(j).act.className != "Roman 216") || (population.at(i).periods.at(templ).act.className == "Roman 216" && population.at(i).periods.at(templ).act.className != "Roman 201")){
            population.at(i).periods.at(j).fitness -= .4;
          }
          else if ((population.at(i).periods.at(j).room.roomName == "Roman 201" && population.at(i).periods.at(j).act.className == "Roman 216") || (population.at(i).periods.at(templ).act.className == "Roman 216" && population.at(i).periods.at(templ).act.className == "Roman 201")){
            population.at(i).periods.at(j).fitness += .5;
          }
          if ((population.at(i).periods.at(j).room.roomName == "Beach 201" && population.at(i).periods.at(j).act.className != "Beach 301") || (population.at(i).periods.at(templ).act.className == "Beach 301" && population.at(i).periods.at(templ).act.className != "Beach 201")){
            population.at(i).periods.at(j).fitness -= .4;
          }
          else if ((population.at(i).periods.at(j).room.roomName == "Beach 201" && population.at(i).periods.at(j).act.className == "Beach 301") || (population.at(i).periods.at(templ).act.className == "Beach 301" && population.at(i).periods.at(templ).act.className == "Beach 201")){
            population.at(i).periods.at(j).fitness += .5;
          }
        }
        if ((population.at(i).periods.at(j).act.className == "SLA191A" || population.at(i).periods.at(j).act.className == "SLA191B") && (population.at(i).periods.at(templ).act.className == "SLA100A" || population.at(i).periods.at(templ).act.className == "SLA100B")){
          if ((population.at(i).periods.at(j).room.roomName == "Roman 201" && population.at(i).periods.at(j).act.className != "Roman 216") || (population.at(i).periods.at(templ).act.className == "Roman 216" && population.at(i).periods.at(templ).act.className != "Roman 201")){
            population.at(i).periods.at(j).fitness -= .4;
          }
          else if ((population.at(i).periods.at(j).room.roomName == "Roman 201" && population.at(i).periods.at(j).act.className == "Roman 216") || (population.at(i).periods.at(templ).act.className == "Roman 216" && population.at(i).periods.at(templ).act.className == "Roman 201")){
            population.at(i).periods.at(j).fitness += .5;
          }
          if ((population.at(i).periods.at(j).room.roomName == "Beach 201" && population.at(i).periods.at(j).act.className != "Beach 301") || (population.at(i).periods.at(templ).act.className == "Beach 301" && population.at(i).periods.at(templ).act.className != "Beach 201")){
            population.at(i).periods.at(j).fitness -= .4;
          }
          else if ((population.at(i).periods.at(j).room.roomName == "Beach 201" && population.at(i).periods.at(j).act.className == "Beach 301") || (population.at(i).periods.at(templ).act.className == "Beach 301" && population.at(i).periods.at(templ).act.className == "Beach 201")){
            population.at(i).periods.at(j).fitness += .5;
          }
        }
      }
      templ++;
      if (tempm < population.at(i).periods.size()){
        if ((population.at(i).periods.at(j).act.className == "SLA100A" || population.at(i).periods.at(j).act.className == "SLA100B") && (population.at(i).periods.at(tempm).act.className == "SLA191A" || population.at(i).periods.at(tempm).act.className == "SLA191B")){
          population.at(i).periods.at(j).fitness += .25;
        }
        if ((population.at(i).periods.at(j).act.className == "SLA191A" || population.at(i).periods.at(j).act.className == "SLA191B") && (population.at(i).periods.at(tempm).act.className == "SLA100A" || population.at(i).periods.at(tempm).act.className == "SLA100B")){
          population.at(i).periods.at(j).fitness += .25;
        }
      }
      tempm++;
    }
  }
  for (int i = 0; i < 1; i++){
    for (int j = 0; j < population.at(i).periods.size(); j++){
      cout << "Population: " << i << endl;
      cout << "After Specific Fitness: " << population.at(i).periods.at(j).fitness << endl;
      cout << endl;
    }
  }
}

bool compare(schedule a, schedule b){
  return a.totalFitness > b.totalFitness;
}

void geneticAlg(vector<schedule> &population, string facilitators[10], string times[6], vector<activities> acts, vector<rooms> roomVec){
  vector<schedule> newPopulation;
  vector<schedule> nextGen;
  schedule tempSchedule;
  period tempPeriod;
  vector<period> offSpring;
  string tempFac;
  int randomNum, mutateNum;
  float fitness = 0;
  checkRoom(population);
  checkActivity(population);
  checkFacilitator(population);
  checkSpecific(population);
  for (int i = 0; i < population.size(); i++){
    fitness = 0;
    for (int j = 0; j < population.at(i).periods.size(); j++){
      fitness += population.at(i).periods.at(j).fitness;
    }
    population.at(i).totalFitness = fitness;
  }
  cout << "\nPopulation Fitness: " << population.size() << endl;
  for (int i = 0; i < population.size(); i++){
    cout << population.at(i).totalFitness << " ";
  }
  cout << endl;
  cout << "After sorting: " << endl;
  sort(population.begin(),population.end(), compare);
  cout << "\nPopulation after sort: " << endl;
  for (int i = 0; i < population.size(); i++){
    cout << population.at(i).totalFitness << " ";
  }
  for (int i = 0; i < population.size()/2; i++){
    tempSchedule = population.at(i);
    newPopulation.push_back(tempSchedule);
  }
  cout << "\nNew population: " << newPopulation.size() << endl;
  for (int i = 0; i < newPopulation.size(); i++){
    cout << newPopulation.at(i).totalFitness << " ";
  }
  cout << endl;
  for (int i = 0; i < newPopulation.size(); i++){
    for (int j = 1; j < newPopulation.size()-1; j++){
      offSpring.clear();
      for (int l = 0; l < 3; l++){
        tempPeriod = newPopulation.at(i).periods.at(l);
        offSpring.push_back(tempPeriod);
      }
      for (int k = 3; k < 6; k++){
        tempPeriod = newPopulation.at(j).periods.at(k);
        offSpring.push_back(tempPeriod);
      }
      tempSchedule.periods = offSpring;
    }
    nextGen.push_back(tempSchedule);
  }
  cout << "NextGen size: " << nextGen.size() << endl;
  cout << "NextGen period size: " << nextGen.at(100).periods.size() << endl;
  for (int i = 0; i < newPopulation.size(); i++){
    offSpring.clear();
    for (int j = 0; j < newPopulation.at(i).periods.size(); j++){
      tempPeriod = newPopulation.at(i).periods.at(j);
      offSpring.push_back(tempPeriod);
      tempSchedule.periods = offSpring;
    }
    nextGen.push_back(tempSchedule);
  }
  cout << "Full NextGen size: " << nextGen.size() << endl;
  cout << "Full NextGen period size: " << nextGen.at(390).periods.size() << endl;
  randomNum = rand() % 4;
  cout << "RandomNum: " << randomNum << endl;
  cout << "Pre mutate: " << nextGen.at(0).periods.at(0).facilitator << " " << nextGen.at(0).periods.at(0).time << " " << nextGen.at(0).periods.at(0).act.className << " " << nextGen.at(0).periods.at(0).room.roomName << endl;
  for (int i = 0; i < 1; i++){
    for (int j = 0; i < nextGen.at(i).periods.size(); j++){
      cout << "check 1" << endl;
      if (randomNum == 0){
        tempFac = facilitators[mutateNum];
        nextGen.at(i).periods.at(j).facilitator = tempFac;
        cout << "check 2" << endl;
      }
      if (randomNum == 1){
        cout << "check 3" << endl;
        break;
      }
      if (randomNum == 2){
        mutateNum = rand() % (acts.size()-1);
        nextGen.at(i).periods.at(j).act = acts.at(mutateNum);
        cout << "check 4" << endl;
      }
      if (randomNum == 3){
        mutateNum = rand() % (roomVec.size()-1);
        nextGen.at(i).periods.at(j).room = roomVec.at(mutateNum);
        cout << "check 4" << endl;
      }
      cout << "check 5" << endl;
    }
  }
  cout << "check 6" << endl;
  cout << "Post mutate: " << nextGen.at(0).periods.at(0).facilitator << " " << nextGen.at(0).periods.at(0).time << " " << nextGen.at(0).periods.at(0).act.className << " " << nextGen.at(0).periods.at(0).room.roomName << endl;
}

int main() {
  vector<schedule> population;
  string facilitators[10] = {"Lock", "Glen", "Banks", "Richards", "Shaw", "Singer", "Uther", "Tyler", "Numen", "Zeldin"};
  string times[6] = {"10 AM", "11 AM", "12 PM", "1 PM", "2 PM", "3 PM"};
  vector<activities> actVec;
  vector<rooms> roomVec;
  activities tempAct = {"SLA100A", 50, {"Glen", "Lock", "Banks", "Zeldin"},{"Numen", "Richards"}};
  rooms tempRoom = {"Slater 003", 45};
  actVec.push_back(tempAct);
  roomVec.push_back(tempRoom);
  tempAct = {"SLA100B", 50, {"Glen", "Lock", "Banks", "Zeldin"},{"Numen", "Richards"}};
  actVec.push_back(tempAct);
  tempAct = {"SLA191A", 50, {"Glen", "Lock", "Banks", "Zeldin"}, {"Numen", "Richards"}};
  actVec.push_back(tempAct);
  tempAct = {"SLA191B", 50, {"Glen", "Lock", "Banks", "Zeldin"}, {"Numen", "Richards"}};
  actVec.push_back(tempAct);
  tempAct = {"SLA201", 50, {"Glen", "Banks", "Zeldin", "Shaw"}, {"Numen", "Richards", "Singer"}};
  actVec.push_back(tempAct);
  tempAct = {"SLA291", 50, {"Lock", "Banks", "Zeldin", "Singer"}, {"Numen", "Richards", "Singer"}};
  actVec.push_back(tempAct);
  tempAct = {"SLA303", 60, {"Glen", "Zeldin", "Banks"}, {"Numen", "Singer", "Shaw"}};
  actVec.push_back(tempAct);
  tempAct = {"SLA304", 25, {"Glen", "Banks", "Tyler"}, {"Numen", "Singer", "Shaw", "Richards", "Uther", "Zeldin"}};
  actVec.push_back(tempAct);
  tempAct = {"SLA394", 20, {"Tyler", "Singer"}, {"Richards", "Zeldin"}};
  actVec.push_back(tempAct);
  tempAct = {"SLA449", 60, {"Tyler", "Singer", "Shaw"}, {"Zeldin", "Uther"}};
  actVec.push_back(tempAct);
  tempAct = {"SLA451", 100, {"Tyler", "Singer", "Shaw"}, {"Zeldin", "Uther", "Richards", "Banks"}};
  actVec.push_back(tempAct);
  tempRoom = {"Roman 216", 30};
  roomVec.push_back(tempRoom);
  tempRoom = {"Loft 206", 75};
  roomVec.push_back(tempRoom);
  tempRoom = {"Roman 201", 50};
  roomVec.push_back(tempRoom);
  tempRoom = {"Loft 310", 108};
  roomVec.push_back(tempRoom);
  tempRoom = {"Beach 201", 60};
  roomVec.push_back(tempRoom);
  tempRoom = {"Beach 301", 75};
  roomVec.push_back(tempRoom);
  tempRoom = {"Logos 325", 450};
  roomVec.push_back(tempRoom);
  tempRoom = {"Frank 119", 60};
  roomVec.push_back(tempRoom);
  population = scheduleGen(facilitators, times, actVec, roomVec);
  geneticAlg(population, facilitators, times, actVec, roomVec);
}