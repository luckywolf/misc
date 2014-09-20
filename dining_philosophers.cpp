/* 
http://code.msdn.microsoft.com/windowsdesktop/Dining-Philosophers-in-C-11-f6bb06a8
*/

class Chopstick 
{ 
public: 
    Chopstick(){}; 
    mutex m; 
}; 

auto eat = [](Chopstick* leftChopstick, Chopstick* rightChopstick, int philosopherNumber) 
{ 
    if (leftChopstick == rightChopstick) 
        throw exception("Left and right chopsticks should not be the same!"); 
 
    lock(leftChopstick->m, rightChopstick->m);    // ensures there are no deadlocks 
    lock_guard<mutex> a(leftChopstick->m, adopt_lock); 
    lock_guard<mutex> b(rightChopstick->m, adopt_lock);                     
 
    string pe = "Philosopher " + to_string(philosopherNumber) + " eats.\n"; 
    cout << pe; 
 
    //std::chrono::milliseconds timeout(500); 
    //std::this_thread::sleep_for(timeout); 
}; 

static const int numPhilosophers = 5; 
 
// 5 utencils on the left and right of each philosopher. Use them to acquire locks. 
vector< unique_ptr<Chopstick> > chopsticks(numPhilosophers); 
 
for (int i = 0; i < numPhilosophers; ++i) 
{ 
    auto c1 = unique_ptr<Chopstick>(new Chopstick()); 
    chopsticks[i] = move(c1); 
} 

// This is where we create philosophers, each of 5 tasks represents one philosopher. 
vector<thread> tasks(numPhilosophers); 
 
tasks[0] = thread(eat,  
        chopsticks[0].get(),                        // left chopstick:  #1 
        chopsticks[numPhilosophers - 1].get(),        // right chopstick: #5 
        0 + 1,                                        // philosopher number 
        1, 
        numPhilosophers 
    ); 
 
for (int i = 1; i < numPhilosophers; ++i) 
{ 
    tasks[i] = (thread(eat,  
            chopsticks[i - 1].get(),                // left chopstick 
            chopsticks[i].get(),                    // right chopstick 
            i + 1,                                    // philosopher number 
            i, 
            i + 1 
            ) 
        ); 
} 


// May eat! 
for_each(tasks.begin(), tasks.end(), mem_fn(&thread::join)); 

/* 
   Philosopher 1 picked 1 chopstick. 
   Philosopher 3 picked 2 chopstick. 
   Philosopher 1 picked 5 chopstick. 
   Philosopher 3 picked 3 chopstick. 
Philosopher 1 eats. 
Philosopher 3 eats. 
   Philosopher 5 picked 4 chopstick. 
   Philosopher 2 picked 1 chopstick. 
   Philosopher 2 picked 2 chopstick. 
   Philosopher 5 picked 5 chopstick. 
Philosopher 2 eats. 
Philosopher 5 eats. 
   Philosopher 4 picked 3 chopstick. 
   Philosopher 4 picked 4 chopstick. 
Philosopher 4 eats. 
*/
