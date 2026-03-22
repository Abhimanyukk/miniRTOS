# 🎯 Project Goal

Build a:

> **Deterministic Embedded Runtime (Scheduler + Logging)**
> that is:

* Testable on desktop (Docker)
* Portable to MCU (ESP32, STM32, etc.)
* Cleanly architected

---

# 🧱 1. High-Level Architecture

Split into **3 strict layers**:

```
Application
   ↓
Core (Scheduler + Logging)
   ↓
Platform Layer (HAL / Time / IO)
```

---

## 🔹 Core Layer (Platform Independent)

* Scheduler
* Logger
* Config
* No hardware dependencies ❌

👉 Pure C (portable)

---

## 🔹 Platform Layer (Porting Layer)

Abstract:

* Time source
* UART / output
* Critical sections

---

## 🔹 Application Layer

* Your demo apps
* Tests
* Examples

---

# 📂 2. Repository Structure

```bash
microflow/
│
├── core/
│   ├── scheduler/
│   ├── logger/
│   ├── config/
│
├── platform/
│   ├── linux/
│   ├── esp32/
│   ├── stm32/
│
├── apps/
│   ├── demo_blink/
│   ├── demo_tasks/
│
├── tests/
│   ├── unit/
│   ├── integration/
│
├── tools/
│   ├── log_parser.py
│
├── docker/
│   └── Dockerfile
│
├── CMakeLists.txt
└── README.md
```

---

# ⚙️ 3. Core Design

## 🧠 Scheduler API

```c
void scheduler_init(void);
void scheduler_add_task(task_fn fn, uint32_t period_ms);
void scheduler_run(void);
```

---

## 🧠 Logger API

```c
void log_init(void);
void log_write(uint8_t level, const char *fmt, ...);
```

Macros:

```c
#define LOG_INFO(...)  log_write(LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_ERROR(...) log_write(LOG_LEVEL_ERROR, __VA_ARGS__)
```

---

## 🔹 Platform Interface (VERY IMPORTANT)

```c
uint32_t platform_get_time_ms(void);
void platform_log_output(const char *msg);
void platform_enter_critical(void);
void platform_exit_critical(void);
```

👉 This makes your core portable everywhere

---

# 🐳 4. Docker-Based Development & Testing

This is your **big advantage**

---

## 🔹 Why Docker?

* No toolchain mess
* Reproducible builds
* CI-ready

---

## 🔹 Dockerfile

```Dockerfile
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3 \
    python3-pip

WORKDIR /app
```

---

## 🔹 Build inside Docker

```bash
docker build -t microflow .
docker run -it -v $(pwd):/app microflow bash
```

---

## 🔹 Build system

Use CMake

```bash
mkdir build && cd build
cmake ..
make
```

---

# 🧪 5. Testing Strategy (CRITICAL)

## 🔹 Unit Tests (Core logic)

Use:

* Unity *(lightweight)*

Test:

* Task scheduling correctness
* Log buffer handling

---

## 🔹 Integration Tests (Linux platform)

Simulate:

* Time progression
* Task execution

---

## 🔹 Example Test

```c
void test_scheduler_runs_task(void) {
    int counter = 0;

    void task() { counter++; }

    scheduler_add_task(task, 100);

    simulate_time(100);
    scheduler_run_once();

    TEST_ASSERT_EQUAL(1, counter);
}
```

---

# 🖥️ 6. Linux Platform Implementation

This is your **first target**

---

## 🔹 Time

```c
uint32_t platform_get_time_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}
```

---

## 🔹 Logging

```c
void platform_log_output(const char *msg) {
    printf("%s\n", msg);
}
```

---

# 🔌 7. MCU Integration Plan

After Linux works → port to MCU

---

## 🔹 Step 1: ESP32 (Good start)

Use:

* ESP-IDF *(only for build/flash, not logic)*

Map:

* `platform_get_time_ms()` → `esp_timer_get_time()/1000`
* UART → `printf` or UART driver

---

## 🔹 Step 2: STM32

Use:

* HAL or bare-metal

Map:

* SysTick → time
* UART → logging

---

# ⚡ 8. Key Engineering Decisions

## 🔹 No dynamic memory

* Avoid `malloc`
* Use static buffers

---

## 🔹 Deterministic logging

* Fixed-size ring buffer

---

## 🔹 Compile-time config

```c
#define MAX_TASKS 8
#define LOG_BUFFER_SIZE 32
```

---

# 🔥 9. Advanced Features Roadmap

Add later:

* Task priorities
* Deadline monitoring
* Log compression
* Binary logging protocol
* PC visualiser tool

---

# 📈 10. CI/CD (Optional but Powerful)

Use:

* GitHub Actions

Run:

* Build in Docker
* Run tests
* Static analysis

---

# 🧭 Development Timeline

## Week 1:

* Core scheduler + Linux platform

## Week 2:

* Logger + integration

## Week 3:

* Unit tests + Docker setup

## Week 4:

* ESP32 port

---

# 💬 Final Thought

This approach gives you:

* Clean architecture ✅
* Cross-platform proof ✅
* Testability (rare in embedded) ✅
* Real engineering credibility ✅

---

If you want next, I can:

✅ Write **starter code for full project (ready to clone)**
✅ Design **logger ring buffer + scheduler internals deeply**
✅ Help you create a **production-grade README (very important)**

Just tell me 👍
