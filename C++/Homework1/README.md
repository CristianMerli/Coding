# Homework-1 structure
---
## Files and folders for the course TPA: homework-1.
---
- `data:` folder containing I/O files.
  - `input:` folder containing input matrix and convolution kernel.
  - `output:` folder containing test output matrices.
- `doc:` folder containing homework initial documentation.
- `src:` folder containing source code.
  - `lib:` folder containing libraries.
  - `main:` folder containing main homework file (.cpp).
- `homework.exe:` homework executable generated using makefile.
- `makefile:` use command **make** to compile, ***make run*** to execute or ***make all_run*** to compile and execute.
---
## Notes:
---
- The matrix convolution is applied on input matrix after ReLU operation (which modifies the matrix)!
- All the other operations are directly applied on input matrix.
---
