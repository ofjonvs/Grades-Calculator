/* Jonas da Silva, 119289334, jdasilva*/

#include <stdio.h>
#include <math.h>

#define MAXASSIGNMENTS 50

/* prototypes*/
double calculate_numeric_score(int data_array[], int total_assignments,
			       int dropped_assignments);
double calculate_mean(int data_array[], int total_assignments);
void late_deduction(int late_array[], int total_assignments, int late_penalty);
double calculate_standard_deviation(int data_array[], int total_assignments, double mean);
int valid_weight(int data_array[], int total_assignments);

/* main */
int main(){
  int late_penalty, dropped_assignments, num_assignments, i = 0, j = 0;
  double numeric_score, mean, standard_deviation;
  char stats;
  int assignment_data[MAXASSIGNMENTS * 4];
  int assignment_data_late[MAXASSIGNMENTS * 4];

  
  /* reading info */
  scanf("%d %d %c", &late_penalty, &dropped_assignments, &stats);
  scanf("%d", &num_assignments); 
  if(num_assignments > MAXASSIGNMENTS || num_assignments < 0 || late_penalty < 0
     || dropped_assignments > num_assignments || !(stats == 'y' || stats == 'Y'||
						 stats == 'n' || stats == 'N') ){
    printf("Invalid values provided\n");
    return 0;
  }

  /* reading assignment information */
  for(i = 0; i < num_assignments * 4; i++){
    scanf( "%d,", &assignment_data[i]);
  }

  if(!valid_weight(assignment_data, num_assignments)){
    printf("Invalid values privided\n");
    return 0;
  }

  /* copying data */
  for(i = 0; i < MAXASSIGNMENTS * 4; i++){
    assignment_data_late[i] = assignment_data[i];
  }

  /* calculations */
  late_deduction(assignment_data_late, num_assignments, late_penalty);
  mean = calculate_mean(assignment_data_late, num_assignments);
  standard_deviation = calculate_standard_deviation(assignment_data_late, num_assignments, mean);
  numeric_score = calculate_numeric_score(assignment_data_late, num_assignments,
					 dropped_assignments);
  
  /* print output */
  printf("Numeric Score: %5.4f\n", numeric_score);
  printf("Points Penalty Per Day Late: %d\n", late_penalty);
  printf("Number of Assignments Dropped: %d\n", dropped_assignments);
  printf("Values Provided:\nAssignment, Score, Weight, Days Late\n");

  for(i = 1; i <= num_assignments; i++){
    for(j = 0; j < num_assignments * 4; j +=4){
      if(assignment_data[j] == i){
	printf("%d, %d, %d, %d\n", assignment_data[j], assignment_data[j+1],
	       assignment_data[j+2], assignment_data[j+3]);
      }
    }
  }

  if(stats == 'y' || stats == 'Y'){
    printf("Mean: %5.4f, Standard Deviation: %5.4f\n", mean, standard_deviation);
  }


  return 0;
}


/* calculates mean. Takes in array and number of assignments */
double calculate_mean(int data_array[], int total_assignments){
  int i, j = 1;
  double  mean = 0;

  /* adds up all scores */
  for(i = 0; i < total_assignments; i++){
    mean += data_array[j];
    j += 4;
  }

  /* divides total scores by number of assignments */
  mean = mean / i ;
  return mean;
}

/* calculates numeric score. Takes in array, number of assignments and 
   number of assignments dropped */
double calculate_numeric_score(int data_array[], int total_assignments,
			       int dropped_assignments){
  int i, k, dropped_score, dropped_weighted_score;
  double num_score = 0, weight = 100, dropped_weight;

  /* Sets values of lowest value assignments to -1 */
  for(i = 0; i < dropped_assignments; i++){
    dropped_weighted_score = 10001;
    for(k = 1; k < total_assignments * 4; k += 4){
      if(data_array[k] != -1){
	if(dropped_weighted_score > data_array[k] * data_array[k + 1]){
	  dropped_score = data_array[k];
	  dropped_weighted_score = data_array[k] * data_array[k + 1];
	  dropped_weight = data_array[k+1];
	}	 
      }  
    }
    weight -= dropped_weight;
    for(k = 1; k < (total_assignments * 4) + 1; k += 4){
      if(dropped_score == data_array[k]){
	data_array[k] = -1;
      }
    }
  }

  /* Adds up weighted scores then divides by the total weight */
  for(i = 1; i < (total_assignments * 4) + 1; i += 4){
    if(data_array[i] == -1){
      continue;
    }
    num_score += data_array[i] * data_array[i+1];
  }
  num_score /= weight;
  return num_score;
}

/* decreases scores of assignments based on the late day penalty and 
   amount of days late */
void late_deduction(int late_array[], int total_assignments, int late_penalty){
  int i;

  /* subtracts late penalty times days late of each assignment from score */
  for(i = 1; i < (total_assignments * 4) + 1; i += 4){
    late_array[i] -= late_array[i + 2] * late_penalty;
  }
}

/* calculates standard deviation */
double calculate_standard_deviation(int data_array[], int total_assignments, double mean){
  int i;
  double  standard_deviation = 0;

  /*sums up total of scores minus mean sqaured */
  for(i = 1; i < total_assignments * 4; i += 4){
    standard_deviation += (data_array[i] - mean) * (data_array[i] - mean);
  }

  /*takes root of above calulation divided by number of assignments */
  standard_deviation = sqrt(standard_deviation / total_assignments);
  return standard_deviation;
}

/* checks if weight of all assignments is equal to 100 */
int valid_weight(int data_array[], int total_assignments){
  int i, sum = 0;

  /* Adds weights of all assignments */
  for(i = 2; i < total_assignments * 4; i += 4){
    sum += data_array[i];
  }

  if(sum == 100){
    return 1;
  }
  return 0;
}


