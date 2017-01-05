#pragma once
#include <chrono>

namespace sparky {
    class Timer {
    private:
        std::chrono::time_point<std::chrono::steady_clock> m_begin;
    public:
        Timer() :
            m_begin(std::chrono::high_resolution_clock::now())
        {}
        ~Timer() {}

        void reset() {
            m_begin = std::chrono::high_resolution_clock::now();
        }

        //Ĭ���������  
        int64_t elapsed() const
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
        }
        //΢��  
        int64_t elapsed_micro() const
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
        }
        //����  
        int64_t elapsed_nano() const
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
        }
        //��  
        int64_t elapsed_seconds() const
        {
            return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
        }
        //��  
        int64_t elapsed_minutes() const
        {
            return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - m_begin).count();
        }
        //ʱ  
        int64_t elapsed_hours() const
        {
            return std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - m_begin).count();
        }
    };
}