#include "thread_sample.hpp"

int main(void)
{
    SampleThread st;
    const int sleep_msec = 100;

    st.GenerateThread();
    int counter = 0;
    int value = 0;

    while(1)
    {
        counter = st.GetCounter();
        value = st.GetValue();

        printf("Counter: %d Value:%d", counter, value);

        if(counter % 10 == 0)
        {
            printf(" --> Value Reset");
            st.ResetValue(10);
        }
        printf("\n");
        
        std::this_thread::sleep_for(std::chrono::microseconds(sleep_msec));
    }

    st.CloseThread();
    return(0);
}