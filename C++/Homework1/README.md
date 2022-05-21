# Homework-1 structure
---
## Files and folders for the course TPA: homework-1.
---
- `data:` folder containing I/O files.
  - `input:` folder containing input matrix and convolution kernel.
  - `output:` folder containing test output matrices.
- `doc:` folder containing homework initial documentation.
  - `code:` folder containing code tools & tips.
  - `files:` folder containing project requests and initial data.
- `src:` folder containing source code.
  - `lib:` folder containing code libraries & packages.
  - `main:` folder containing main code homework files.
- `homework.exe:` homework executable generated using makefile.
- `makefile:` use command **make** to compile, ***make run*** to execute or ***make all_run*** to compile and execute.
---
## Notes:
---
- The matrix convolution is applied on input matrix after ReLU operation (which modifies the matrix)!
- All the other operations are directly applied on input matrix.
---
