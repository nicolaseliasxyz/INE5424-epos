// EPOS Periodic Thread Component Test Program

#include <time.h>
#include <real-time.h>
#include <utility/geometry.h>

using namespace EPOS;

const unsigned int iterations = 100;
const Milisecond period_a = 100;
const Milisecond period_b = 80;
const Milisecond period_c = 60;
const Milisecond wcet_a = 50;
const Milisecond wcet_b = 20;
const Milisecond wcet_c = 10;

Semaphore meu_lock;
volatile unsigned int eu_deveria_ser_um = 0;

int func_a();
int func_b();
int func_c();

OStream cout;
Chronometer chrono;

Periodic_Thread * thread_a;
Periodic_Thread * thread_b;
Periodic_Thread * thread_c;

Point<long, 2> p, p1(2131231, 123123), p2(2, 13123), p3(12312, 123123);

unsigned long base_loop_count;

void callibrate()
{
    chrono.start();
    Microsecond end = chrono.read() + Microsecond(1000000UL);

    base_loop_count = 0;

    while(chrono.read() < end) {
        p = p + Point<long, 2>::trilaterate(p1, 123123, p2, 123123, p3, 123123);
        base_loop_count++;
    }

    chrono.stop();

    base_loop_count /= 1000;
}

inline void exec(char c, Milisecond time = 0)
{
    Milisecond elapsed = chrono.read() / 1000;
    Milisecond end = elapsed + time;

    cout << "\n" << elapsed << " " << c
         << " [A={i=" << thread_a->priority() << ",d=" << thread_a->criterion().deadline() / Alarm::frequency() << ",c=" << thread_a->statistics().job_utilization << "}"
         <<  " B={i=" << thread_b->priority() << ",d=" << thread_b->criterion().deadline() / Alarm::frequency() << ",c=" << thread_b->statistics().job_utilization << "}"
         <<  " C={i=" << thread_c->priority() << ",d=" << thread_c->criterion().deadline() / Alarm::frequency() << ",c=" << thread_c->statistics().job_utilization << "}]";

    while(elapsed < end) {
        for(unsigned long i = 0; i < time; i++)
            for(unsigned long j = 0; j < base_loop_count; j++) {
                p = p + Point<long, 2>::trilaterate(p1, 123123, p2, 123123, p3, 123123);
        }
        elapsed = chrono.read() / 1000;
        cout << "\n" << elapsed << " " << c
             << " [A={i=" << thread_a->priority() << ",d=" << thread_a->criterion().deadline() / Alarm::frequency() << ",c=" << thread_a->statistics().job_utilization << "}"
             <<  " B={i=" << thread_b->priority() << ",d=" << thread_b->criterion().deadline() / Alarm::frequency() << ",c=" << thread_b->statistics().job_utilization << "}"
             <<  " C={i=" << thread_c->priority() << ",d=" << thread_c->criterion().deadline() / Alarm::frequency() << ",c=" << thread_c->statistics().job_utilization << "}]";
    }
}


int main()
{
    cout << "Periodic Thread Component Test" << endl;

    cout << "\nThis test consists in creating three periodic threads as follows:" << endl;
    cout << "- Every " << period_a << "ms, thread A executes \"a\" for " << wcet_a << "ms;" << endl;
    cout << "- Every " << period_b << "ms, thread B executes \"b\" for " << wcet_b << "ms;" << endl;
    cout << "- Every " << period_c << "ms, thread C executes \"c\" for " << wcet_c << "ms;" << endl;

    cout << "\nCallibrating the duration of the base execution loop: ";
    callibrate();
    cout << base_loop_count << " iterations per ms!" << endl;

    cout << "\nThreads will now be created and I'll wait for them to finish..." << endl;

    // p,d,c,act,t
    thread_a = new Periodic_Thread(RTConf(period_a * 1000, 0, wcet_a * 1000, 0, iterations), &func_a);
    thread_b = new Periodic_Thread(RTConf(period_b * 1000, 0, wcet_b * 1000, 0, iterations), &func_b);
    thread_c = new Periodic_Thread(RTConf(period_c * 1000, 0, wcet_c * 1000, 0, iterations), &func_c);

    cout << "This is a GLLF test. This is the GLLF queue. Its supossed to have " << Traits<System>::CPUS << " heads and 1 queue" << endl;
    
    cout << "\nThread A is in queue \"" << thread_a->criterion().queue() << "\nThread B is in queue: " << thread_b->criterion().queue() << "\nThread C is in queue \"" << thread_c->criterion().queue() << endl;


    exec('M');

    chrono.reset();
    chrono.start();

    int status_a = thread_a->join();
    int status_b = thread_b->join();
    int status_c = thread_c->join();

    chrono.stop();

    exec('M');

    cout << "\n... done!" << endl;
    cout << "\n\nThread A exited with status \"" << char(status_a)
         << "\", thread B exited with status \"" << char(status_b)
         << "\" and thread C exited with status \"" << char(status_c) << "." << endl;

    cout << "\nThread A time in total: " << thread_a->criterion().statistics().thread_execution_time << " all cores: " << endl;
    for (unsigned int i = 0; i < CPU::cores(); i ++)
        cout << "\n In Core " << i << " : " << thread_a->criterion().statistics().execution_per_cpu[i] << endl;

    cout << "\nThread B time in total: " << thread_b->criterion().statistics().thread_execution_time << " all cores: " << endl;
    for (unsigned int i = 0; i < CPU::cores(); i ++)
        cout << "\n In Core " << i << " : " << thread_b->criterion().statistics().execution_per_cpu[i] << endl;

    cout << "\nThread C time in total: " << thread_c->criterion().statistics().thread_execution_time << " all cores: " << endl;
    for (unsigned int i = 0; i < CPU::cores(); i ++)
        cout << "\n In Core " << i << " : " << thread_c->criterion().statistics().execution_per_cpu[i] << endl;

    cout << "I'm also done, bye!" << endl;

    cout << "Eu sou: " << eu_deveria_ser_um << ", eu deveria ser: " << iterations << endl;

    return 0;
}


int func_a()
{
    exec('A');

    do {
        exec('a', wcet_a);
        meu_lock.p();
        eu_deveria_ser_um += 1;
        meu_lock.v();
    } while (Periodic_Thread::wait_next());

    exec('A');

    return 'A';
}

int func_b()
{
    exec('B');

    do {
        exec('b', wcet_b);
    } while (Periodic_Thread::wait_next());

    exec('B');

    return 'B';
}

int func_c()
{
    exec('C');

    do {
        exec('c', wcet_c);
    } while (Periodic_Thread::wait_next());

    exec('C');

    return 'C';
}
