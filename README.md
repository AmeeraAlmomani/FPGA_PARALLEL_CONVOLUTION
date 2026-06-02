# Combining FPGA parallelism and machine learning for efficient image convolution
Official implementation of the paper: **Combining FPGA parallelism and machine learning for efficient image convolution**

Published in *Engineering Research Express*, 2026.

DOI: https://doi.org/10.1088/2631-8695/ae655e

Authors: Ameera Almomani, Doa’a Aloqoul and Abedalmuhdi Almomany*

---

## Abstract
Recent advances in artificial intelligence and deep learning have transformed various fields relying on image processing, including autonomous vehicles, medical imaging, and advanced surveillance systems. A fundamental operation in these applications is image convolution, which requires both high accuracy and real-time performance, thereby demanding efficient acceleration techniques. Field programmable gate arrays (FPGAs) offer an attractive platform due to their reconfigurability and inherent parallelism. This paper proposes a scalable FPGA-based architecture for image convolution, using the Sobel filter as a case study. The proposed design exploits parallel processing by distributing computations across N parallel convolution kernels, while incorporating hardware-oriented optimizations in the Vitis HLS 2024 framework, such as loop unrolling, pipelining, and efficient use of on-chip memory. As a result, the architecture achieves a practical latency reduction that scales approximately with 1/N. Experimental results show that the proposed design reduces latency by up to 73% compared to existing architectures, while maintaining comparable resource utilization and consuming less than 0.4 W, demonstrating its suitability for low-power edge platforms. Furthermore, a machine learning ML-based prediction model is introduced to estimate the optimal number of parallel kernels for a given FPGA configuration. Six machine-learning models were evaluated, including decision tree, random forest (RF), support vector regression, K-nearest neighbors, gradient boosting, and XGBoost. Among them, RF and XGBoost achieved high accuracy on the full dataset and maintained strong performance under cross-family evaluation, demonstrating good generalization to unseen FPGA platforms. These results highlight the effectiveness of combining FPGA-based acceleration with ML for scalable and efficient design space exploration in real-time edge computing.

---
## Methodology Overview
<img width="753" height="613" alt="ML_FPGA2" src="https://github.com/user-attachments/assets/e61c887a-2267-44c6-a7f9-ae9607b2ea1f" />

---
## Repository Structure

```text
.
├── hls/
├── notebooks/
├── dataset/
└── README.md
```
---

## Requirements

### HLS Design
- AMD Vitis HLS 2024.2

### Model Training and Evaluation
- Google Colab
- Python 3.x

---
## Reproducing the Results
### Hardware Implementation (HLS Design)
The HLS implementation is located in:

```text
hls/
```
Testbench files are located in:

```text
hls/tb/
```

### Training & Evaluation on Full Dataset
Run:

```text
notebooks/ML-Full.ipynb
```
### Training & Evaluating Cross-Platform generalization
Run:

```text
notebooks/Cross-Platform.ipynb
```
---

## Citation

If you use this repository, please cite:

```bibtex
@article{almomani2026combining,
  title={Combining FPGA parallelism and machine learning for efficient image convolution},
  author={Almomani, Ameera and Aloqoul, Doa’a and Almomany, Abedalmuhdi},
  journal={Engineering Research Express},
  volume={8},
  number={9},
  pages={095227},
  year={2026},
  publisher={IOP Publishing}
}
```

---

## License

This repository is released under the MIT License.

Third-party files retain their original licenses where applicable.

---

## Contact

For questions regarding the implementation, please open an issue in this repository.
