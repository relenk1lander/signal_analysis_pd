# Signal Analysis

## 1. Sigma (Standard Deviation) Calculation

For each channel $c$ with $N$ total entries:

$$\sigma_{c} = \sqrt{\frac{\sum_{i=1}^{N} ADC_{c,i}}{N}}$$

Where:
- $\sigma_{c}$ is the channel-specific standard deviation
- $ADC_{c,i}$ is the ADC value for channel $c$ at entry $i$
- $N$ is the total number of entries

## 2. Signal Identification

Normalized channel value:
$$\text{normalized value}_{c} = \frac{ADC_{c}}{\sigma_{c}}$$

Signal detection criteria:
- If $\text{normalized value}_{c} < 18$: Not a significant signal
- Find channel with maximum normalized value > 18

## 3. Signal Sum Calculation

For a detected signal channel $k$:

$$\text{signal sum} = \sum_{j \in \{k-1, k, k+1\}} \frac{ADC_{j}}{\sigma_{j}}$$

Considering the channel and its adjacent channels

## 4. Event Selection Metrics

$$\text{valid events percentage} = \frac{\text{number of valid events}}{N_{\text{total}}} \times 100\%$$
---
Photos and some information about the project: https://drive.google.com/file/d/1f-P-xNB61l_ydpfkBB3Gc_ttWzeVIs85/view?usp=sharing



