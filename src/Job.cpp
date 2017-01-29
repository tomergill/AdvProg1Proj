/*
 * Job.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: viki
 */

#include "Job.h"

/*
 * add job to the threadpool
 */
Job::Job(void *(*func)(void *arg), void *arg) : func(func), arg(arg) {
    // TODO Auto-generated constructor stub

}

/*
 * do the jobs
 */
void Job::execute() {
    func(arg);
}

/*
 * delete job
 */
Job::~Job() {
    // TODO Auto-generated destructor stub
}

