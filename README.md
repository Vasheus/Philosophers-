# *This project has been created as part of the 42 curriculum.*

# Philosophers

## Description

This repository contains an implementation of the **Dining Philosophers problem**, a classic concurrency and synchronization exercise from the 42 curriculum.

The project simulates multiple philosophers sitting around a table, each alternating between eating, sleeping, and thinking while competing for a limited number of shared resources (forks). It explores how independent execution flows interact when they must coordinate access to shared data.

---

## Topics Covered

- Multithreading and parallel execution  
- Shared resource management  
- Mutex-based synchronization  
- Race conditions and data consistency  
- Deadlock detection and prevention strategies  
- Starvation problems in concurrent systems  
- Thread lifecycle and coordination  

---

## Concept Overview

This project is based on the **Dining Philosophers problem**, a well-known illustration of concurrency issues in operating systems.

Each philosopher is modeled as an independent thread, and forks are shared resources placed between them. To perform the “eating” action, a philosopher must successfully acquire two shared resources at the same time.

This creates a system where:

- Multiple threads compete for limited resources  
- Access to shared data must be carefully synchronized  
- Incorrect coordination can lead to deadlocks (everyone waiting forever)  
- Poor scheduling can lead to starvation (a philosopher never eating)  

The challenge is to design a solution where all threads operate safely without breaking the rules of concurrency, while ensuring that no philosopher dies due to improper synchronization or timing issues.

At its core, the project demonstrates how **simple shared-resource systems can quickly become complex when executed in parallel**, requiring careful control of execution order and access to shared state.