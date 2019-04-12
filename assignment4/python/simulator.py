'''
CS5250 Assignment 4, Scheduling policies simulator
Sample skeleton program
Input file:
    input.txt
Output files:
    FCFS.txt
    RR.txt
    SRTF.txt
    SJF.txt
'''
import sys
from collections import deque

input_file = 'input.txt'


class Process:
    last_scheduled_time = 0

    def __init__(self, id, arrive_time, burst_time):
        self.id = id
        self.arrive_time = arrive_time
        self.burst_time = burst_time
    # for printing purpose

    def __repr__(self):
        return ('[id %d : arrival_time %d,  burst_time %d]' % (self.id, self.arrive_time, self.burst_time))


def FCFS_scheduling(process_list):
    # store the (switching time, proccess_id) pair
    schedule = []
    current_time = 0
    waiting_time = 0
    for process in process_list:
        if(current_time < process.arrive_time):
            current_time = process.arrive_time
        schedule.append((current_time, process.id))
        waiting_time = waiting_time + (current_time - process.arrive_time)
        current_time = current_time + process.burst_time
    average_waiting_time = waiting_time/float(len(process_list))
    return schedule, average_waiting_time

# Input: process_list, time_quantum (Positive Integer)
# Output_1 : Schedule list contains pairs of (time_stamp, proccess_id) indicating the time switching to that proccess_id
# Output_2 : Average Waiting Time

# Assumptions:
# If a new process arrives during context switch, the stopping process will be appended to the queue first


def RR_scheduling(process_list, time_quantum):
    # store the (switching time, proccess_id) pair
    schedule = []
    current_time = 0
    # waiting_time = finish_time -burst_time - arrive_time
    waiting_time = 0

    # [[process, remain_time]]
    # assert remain_time == 0 when process is finished
    ready_queue = deque()

    for process in process_list:
        if len(ready_queue) == 0:
            ready_queue.append([process, process.burst_time, min(time_quantum, process.burst_time)])
            schedule.append((process.arrive_time, process.id))
            continue
        # else: len(ready_queue) > 0
        running_process = ready_queue[0][0]
        if current_time < running_process.arrive_time:
            # CPU idle
            current_time = running_process.arrive_time
        # therefore current_time >= running_process.arrive_time
        assert current_time <= process.arrive_time
        if current_time == process.arrive_time:
            ready_queue.append([process, process.burst_time, min(time_quantum, process.burst_time)])
            continue
        # else: current_time < process.arrive_time
        # CPU busy, RR until find max(current_time) s.t. current_time < process.arrive_time
        provision_time = current_time + ready_queue[0][2]
        while provision_time <= process.arrive_time:
            if ready_queue[0][1] <= ready_queue[0][2]:
                # process finished
                waiting_time += provision_time - running_process.burst_time - running_process.arrive_time
                ready_queue.popleft()
            else:
                ready_queue[0][1] -= ready_queue[0][2]
                ready_queue[0][2] = min(time_quantum, ready_queue[0][1])
                ready_queue.append(ready_queue.popleft())
            current_time = provision_time
            if len(ready_queue) == 0:
                break
            # else: len(ready_queue) > 0
            schedule.append((current_time, ready_queue[0][0].id))
            provision_time = current_time + ready_queue[0][2]
        # provision_time > process.arrive_time, make current_time == process.arrive_time
        if len(ready_queue) == 0:
            ready_queue.append([process, process.burst_time, min(time_quantum, process.burst_time)])
            schedule.append((process.arrive_time, process.id))
            continue
        # else: len(ready_queue) > 0
        ready_queue[0][1] -= process.arrive_time - current_time
        ready_queue[0][2] -= process.arrive_time - current_time
        current_time = process.arrive_time
        ready_queue.append([process, process.burst_time, min(time_quantum, process.burst_time)])

    # flush ready queue
    provision_time = current_time + ready_queue[0][2]
    while len(ready_queue) > 0:
        running_process = ready_queue[0][0]
        if ready_queue[0][1] <= ready_queue[0][2]:
            # process finished
            waiting_time += provision_time - running_process.burst_time - running_process.arrive_time
            ready_queue.popleft()
        else:
            ready_queue[0][1] -= ready_queue[0][2]
            ready_queue[0][2] = min(time_quantum, ready_queue[0][1])
            ready_queue.append(ready_queue.popleft())
        current_time = provision_time
        if len(ready_queue) == 0:
            break
        # else: len(ready_queue) > 0
        schedule.append((current_time, ready_queue[0][0].id))
        provision_time = current_time + ready_queue[0][2]

    average_waiting_time = waiting_time/float(len(process_list))
    return (schedule, average_waiting_time)


def SRTF_scheduling(process_list):
    return (["to be completed, scheduling process_list on SRTF, using process.burst_time to calculate the remaining time of the current process "], 0.0)


def SJF_scheduling(process_list, alpha):
    return (["to be completed, scheduling SJF without using information from process.burst_time"], 0.0)


def read_input():
    result = []
    with open(input_file) as f:
        for line in f:
            array = line.split()
            if (len(array) != 3):
                print("wrong input format")
                exit()
            result.append(Process(int(array[0]), int(array[1]), int(array[2])))
    return result


def write_output(file_name, schedule, avg_waiting_time):
    with open(file_name, 'w') as f:
        for item in schedule:
            f.write(str(item) + '\n')
        f.write('average waiting time %.2f \n' % (avg_waiting_time))


def main(argv):
    process_list = read_input()
    print("printing input ----")
    for process in process_list:
        print(process)
    print("simulating FCFS ----")
    FCFS_schedule, FCFS_avg_waiting_time = FCFS_scheduling(process_list)
    write_output('FCFS.txt', FCFS_schedule, FCFS_avg_waiting_time)
    print("simulating RR ----")
    RR_schedule, RR_avg_waiting_time = RR_scheduling(
        process_list, time_quantum=2)
    write_output('RR.txt', RR_schedule, RR_avg_waiting_time)
    print("simulating SRTF ----")
    SRTF_schedule, SRTF_avg_waiting_time = SRTF_scheduling(process_list)
    write_output('SRTF.txt', SRTF_schedule, SRTF_avg_waiting_time)
    print("simulating SJF ----")
    SJF_schedule, SJF_avg_waiting_time = SJF_scheduling(
        process_list, alpha=0.5)
    write_output('SJF.txt', SJF_schedule, SJF_avg_waiting_time)


if __name__ == '__main__':
    main(sys.argv[1:])
