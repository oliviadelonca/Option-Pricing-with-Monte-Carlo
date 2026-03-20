## Overview

This academic project is an option pricing engine written in C++. 
It was valuable for understanding how financial derivatives are priced, practicing object-oriented programming and learning how to implement Monte Carlo simulations.
It supports European options (analytical pricing) and American options (Monte Carlo simulation).

---

## Objectives

- Price financial options using different models depending on the product
- Computes Delta
- Build a replicating portfolio to hedge risk
- Test results

---

## Models & Methods

### Black-Scholes (European Options)
- Closed-form analytical pricing formula
- Fast and exact under model assumptions
- Provides both price and Delta directly

### Monte Carlo + Longstaff-Schwartz (American Options)
- Simulates many possible future price paths using Geometric Brownian Motion
- Uses regression to estimate the continuation value
- Handles early exercise
- More computationally expensive but more flexible

### Delta Hedging
- Measures sensitivity of the option price to the underlying asset
- Used to construct a replicating portfolio

---

## Architecture

The project is organized into modular components:

- **Option** : Defines the common structure of all financial options and declares pure virtual methods to compute price and delta
- **EuropeanOption / AmericanOption** : Two specialized classes inheriting from Option, to adapt pricing and delta calculations
- **BlackScholes** : Pricing Engine for European options
- **MonteCarlo** : Pricing Engine for American options
- **StrategyReplication** : Computes Delta and Portfolio value to implements delta hedging
- **Tests Module** : Ensures correctness by comparing with reference values

---

## Challenges & Design Choices

### Regression Choice
- Linear regression chosen for simplicity and stability

### Monte Carlo Accuracy
- Large number of simulations (100,000)

### Reproducibility
- Fixed seed ensures deterministic results

### Testing
- Numerical tolerance set to `1e-4`
