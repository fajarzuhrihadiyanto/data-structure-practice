/**
 * Pusat Informasi Udin Petot
 * Source : https://www.hackerrank.com/contests/sdf-m1/challenges/pusat-informasi-udinpetot
 *
 * @author Fajar Zuhri Hadiyanto
 * @version 1.0
 * @since April 3rd 2021
 * */

// IMPORT PACKAGES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// DEFINE THE QUEUE NODE
typedef struct queueNode_t {
    int time;
    char name[101];
    struct queueNode_t *next;
} QueueNode;

// DEFINE THE QUEUE
typedef struct queue_t {
    QueueNode   *_front,
            *_rear;
    unsigned _size;
} Queue;

// PROTOTYPING
void queue_init(Queue *queue);
bool queue_isEmpty(Queue *queue);
void queue_push(Queue *queue, int time, char *name);
void queue_pop(Queue *queue);
char *queue_front_name(Queue *queue);
int queue_front_time(Queue *queue);
void check(Queue *queue1, Queue *queue2, int time);
void stop(Queue *queue1, Queue *queue2);
int queue_sum_time(Queue *queue);

/**
 * Main Function
 * Description :
 *      This function is used as a main console app
 * */
int main() {
    int time;
    char query[10];

    // PREPARE THE QUEUE
    Queue udin, petot;
    queue_init(&udin);
    queue_init(&petot);

    // INITIALIZE FIRST QUEUE TO UDIN
    bool isUdin = true;

    while(true){

        // GET THE TIME AND QUERY
        scanf("%d %s", &time, query);

        char person[101];
        int serveTime;

        // IF QUERY IS ANTRI ...
        if(strcmp(query, "ANTRI") == 0){

            // ... GET THE PERSON'S NAME AND SERVE TIME
            scanf("%s %d", person, &serveTime);

            // IF QUEUE STATE IS IN UDIN AND QUEUE TIME IN UDIN IS NOT GREATER THAN 60 ...
            if(isUdin && queue_sum_time(&udin) <= 60){
                // ... THEN PUSH NEW ENTRY TO UDIN'S QUEUE
                queue_push(&udin, serveTime, person);

                // SET QUEUE STATE TO PETOT
                isUdin = !isUdin;
            }
            // IF QUEUE STATE IS IN PETOT AND QUEUE TIME IN PETOT IS NOT GREATER THAN 60 ...
            else if (!isUdin && queue_sum_time(&petot) <= 60){
                // ... THEN PUSH NEW ENTRY TO UDIN'S QUEUE
                queue_push(&petot, serveTime, person);

                // SET QUEUE STATE TO UDIN
                isUdin = !isUdin;
            }
            // IF NOT
            else {
                // DISPLAY THE MESSAGE
                printf("%s tidak jadi mengantri\n", person);
            }
        }
        // IF QUERY IS CHECK ...
        else if(strcmp(query, "CHECK") == 0){

            // CHECK THE QUEUE STATE
            check(&udin, &petot, time);
        } else {

            // STOP THE QUEUE
            stop(&udin, &petot);
            break;
        }

    }

    return 0;
}

/**
 * Function queue_init
 * Description :
 *      This function is used to initialize queue.
 *
 * @param queue pointer to queue to be initialized
 * */
void queue_init(Queue *queue) {
    queue->_front = queue->_rear = NULL;
    queue->_size = 0;
}

/**
 * Function queue_isEmpty
 * Description :
 *      This function is used to check if the queue is empty or not
 *
 * @param queue pointer to queue to be checked the emptiness
 * @return true if the queue is empty, else false
 * */
bool queue_isEmpty(Queue *queue) {
    return (queue->_front == NULL && queue->_rear == NULL);
}

/**
 * Function queue_push
 * Description :
 *      This function is used to add new element to queue
 *
 * @param queue pointer to queue to be added by new data
 * @param time time data to be added to the queue
 * @param name name data to be added to the queue
 * */
void queue_push(Queue *queue, int time, char *name) {
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        newNode->time = time;
        strcpy(newNode->name, name);
        newNode->next = NULL;

        if (queue_isEmpty(queue))
            queue->_front = queue->_rear = newNode;
        else {
            queue->_rear->next = newNode;
            queue->_rear = newNode;
        }
    }
}

/**
 * Function queue_pop
 * Description :
 *      This function is used to remove the front element of the queue
 *
 * @param queue pointer to queue to be removed at the front element
 * */
void queue_pop(Queue *queue) {
    if (!queue_isEmpty(queue)) {
        QueueNode *temp = queue->_front;
        queue->_front = queue->_front->next;
        free(temp);

        if (queue->_front == NULL)
            queue->_rear = NULL;
        queue->_size--;
    }
}

/**
 * Function queue_front_name
 * Description :
 *      This function is used to get the name field of front element of the queue
 *
 * @param queue pointer to queue to be gotten of its front element
 * @return field name of the first element of the queue if queue is not empty, else an empty string
 * */
char *queue_front_name(Queue *queue) {
    if (!queue_isEmpty(queue)) {
        return (queue->_front->name);
    }
    return "";
}

/**
 * Function queue_front_time
 * Description :
 *      This function is used to get the time field of front element of the queue
 *
 * @param queue pointer to queue to be gotten of its front element
 * @return field time of the first element of the queue if queue is not empty, else 0
 * */
int queue_front_time(Queue *queue) {
    if (!queue_isEmpty(queue)) {
        return (queue->_front->time);
    }
    return 0;
}

/**
 * Function check
 * Description :
 *      This function is used to check the queue at a certain time
 *      by display who is at the first queue and has served by first queue
 *      Also will display who is at the second queue and has served by second queue
 *
 * @param queue1 pointer to the first queue
 * @param queue2 pointer to the second queue
 * @param time time
 * */
void check(Queue *queue1, Queue *queue2, int time) {
    printf("UDIN\n");

    int udinTime = time;

    if(!queue_isEmpty(queue1)){
        if(udinTime >= queue_front_time(queue1)){

            do {
                printf("%s selesai dilayani\n", queue_front_name(queue1));
                udinTime -= queue_front_time(queue1);
                queue_pop(queue1);
            } while(!queue_isEmpty(queue1) && udinTime > queue_front_time(queue1));

            if(!queue_isEmpty(queue1)){
                printf("%s sedang dilayani\n", queue_front_name(queue1));
            } else {
                printf("Tidak ada yang sedang dilayani\n");
            }
        } else {
            printf("Tidak ada yang selesai dilayani\n");
            printf("%s sedang dilayani\n", queue_front_name(queue1));
        }
    } else {
        printf("Tidak ada yang sedang dilayani\n");
    }

    printf("PETOT\n");

    int petotTime = time;

    if(!queue_isEmpty(queue2)){
        if(petotTime >= queue_front_time(queue2)){
            do {
                printf("%s selesai dilayani\n", queue_front_name(queue2));
                petotTime -= queue_front_time(queue2);
                queue_pop(queue2);
            } while(!queue_isEmpty(queue2) && petotTime > queue_front_time(queue2));

            if(!queue_isEmpty(queue2)){
                printf("%s sedang dilayani\n", queue_front_name(queue2));
            } else {
                printf("Tidak ada yang sedang dilayani\n");
            }
        } else {
            printf("Tidak ada yang selesai dilayani\n");
            printf("%s sedang dilayani\n", queue_front_name(queue2));
        }
    } else {
        printf("Tidak ada yang sedang dilayani\n");
    }
}

/**
 * Function stop
 * Description :
 *      This function is used to stop the queue
 *      by display all person at the first and second queue
 *
 * @param queue1 pointer to the first queue
 * @param queue2 pointer to the second queue
 * */
void stop(Queue *queue1, Queue *queue2) {
    printf("UDIN\n");

    if(!queue_isEmpty(queue1)){
        while(!queue_isEmpty(queue1)){
            printf("%s\n", queue_front_name(queue1));
            queue_pop(queue1);
        }
    } else {
        printf("Kosong\n");
    }

    printf("PETOT\n");
    if(!queue_isEmpty(queue2)){
        while(!queue_isEmpty(queue2)){
            printf("%s\n", queue_front_name(queue2));
            queue_pop(queue2);
        }
    } else {
        printf("Kosong\n");
    }
}

/**
 * Function queue_sum_time
 * Description :
 *      This function is used to get the sum all time of every person in the queue
 *
 * @param queue pointer to the queue
 * @return sum of all time of every person in the queue
 * */
int queue_sum_time(Queue *queue) {
    int sum = 0;
    if(!queue_isEmpty(queue)){
        for(QueueNode *temp = queue->_front; temp != NULL; temp = temp->next){
            sum += temp->time;
        }
    }
    return sum;
}


