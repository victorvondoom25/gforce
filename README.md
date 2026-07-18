# G-ForceZero

G-ForceZero is a highly optimized, UCI-compatible neural network chess engine written in C++. It features a custom native C++ NNUE trainer and an end-to-end self-play pipeline for generating its own training data and improving its evaluation.

## Project Structure

The project has been radically simplified to separate the engine core from the training tools:

```text
G-ForceZero/
├── src/
│   ├── engine/       # Core engine, UCI interface, search algorithms, and syzygy probing
│   └── tools/        # Neural network trainer, self-play data generator, and utilities
├── data/             # Neural networks (.nnue), opening books, and generated self-play data
├── scripts/          # Helper scripts
└── CMakeLists.txt    # Build system
```

## Compilation

G-ForceZero uses CMake. To compile both the engine (`G-ForceZero`) and the training utility (`trainer`), run:

```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

The compiled binaries will be placed in the project root directory.

### GPU Support (CUDA)

If you have an NVIDIA GPU and the CUDA Toolkit installed (`nvcc`), CMake will automatically detect it and compile the GPU-accelerated trainer (`trainCudaNetwork`). If `nvcc` is not in your path, you can specify it explicitly:

```bash
CUDACXX=/usr/local/cuda/bin/nvcc cmake ..
```

## Running the Engine

You can run the engine directly or connect it to any UCI-compatible GUI (like Cute Chess or Arena):

```bash
./G-ForceZero
```

## Training Pipeline

G-ForceZero comes with a complete self-play and training pipeline. The workflow consists of three simple steps:

### 1. Generate Self-Play Data
Generate raw binary training data by having the engine play against itself using a given opening book (e.g. `openings.epd`):
```bash
./trainer selfplay data/openings.epd --threads 4
```
Games are saved to `data/selfplayGames/`. Press `Ctrl+C` at any time to safely stop the process.

### 2. Prepare Training Data
Convert the raw games into shuffled, parsed training binaries ready for the neural network:
```bash
./trainer prepareTrainingData
```
This extracts positions into `data/trainingData/`.

### 3. Train the Network
Train the network using the prepared data:
```bash
# For CPU training
./trainer trainNetwork

# For GPU training (if compiled with CUDA)
./trainer trainCudaNetwork
```
The trainer will output updated `.nnue` files at periodic checkpoints, which you can then test in the engine!
