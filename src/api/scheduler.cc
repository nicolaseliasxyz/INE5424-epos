// EPOS CPU Scheduler Component Implementation

#include <process.h>
#include <time.h>

__BEGIN_SYS

// The following Scheduling Criteria depend on Alarm, which is not available at scheduler.h
template <typename ... Tn>
FCFS::FCFS(int p, Tn & ... an): Priority((p == IDLE) ? IDLE : Alarm::elapsed()) {}

EDF::EDF(const Microsecond & d, const Microsecond & p, const Microsecond & c, unsigned int): Real_Time_Scheduler_Common(Alarm::ticks(d), Alarm::ticks(d), p, c) {}

void EDF::update() {
    if((_priority >= PERIODIC) && (_priority < APERIODIC))
        _priority = Alarm::elapsed() + _deadline;
}

LLF::LLF(const Microsecond & deadline, const Microsecond & period, const Microsecond & capacity, unsigned int): 
    Real_Time_Scheduler_Common((deadline - capacity), Alarm::ticks(deadline),  Alarm::ticks(period),  Alarm::ticks(capacity)) {}

void LLF::update() {
    // _finished_execution é uma flag que indica se a execução da thread foi finalizada, ela eh setada no dispatch
    if (has_stopped_execution) {
        has_stopped_execution = false;
        _capacity = _capacity - (Alarm::elapsed() - _statistics.last_thread_dispatch);
    }
    if((_priority >= PERIODIC) && (_priority < APERIODIC))
        _priority = _deadline - (Alarm::elapsed() + _capacity);
}

// TODO: Trocar para nova estatistica ao inves de usar last_thread_dispatch 
void LLF::set_start_execution() { _statistics.last_thread_dispatch = Alarm::elapsed(); }

// Since the definition of FCFS above is only known to this unit, forcing its instantiation here so it gets emitted in scheduler.o for subsequent linking with other units is necessary.
template FCFS::FCFS<>(int p);

__END_SYS
