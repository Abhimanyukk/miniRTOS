# miniRTOS

Deterministic Embedded Runtime (Scheduler + Logging) — testable on desktop, portable to MCU.

## Build (Linux / Docker)

```bash
mkdir build && cd build
cmake ..
make
```

## Run

```bash
./build/minirtos_app
```

## Docker

```bash
docker build -t minirtos -f docker/Dockerfile .
docker run -it -v $(pwd):/app minirtos bash
```

## Project Structure

```
core/           Core portable logic (scheduler, logger, config)
platform/       Platform abstraction layer (linux, esp32, stm32)
apps/           Demo applications and main entry point
tests/          Unit and integration tests
tools/          Utilities (log parser)
docker/         Docker build environment
```
