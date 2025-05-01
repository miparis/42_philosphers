Here's a complete and well-structured `README.md` file for your **Philosophers** project, based entirely on the context and details you provided:

---

# 🧠 Philosophers

The **Philosophers** project is an implementation of the classic **Dining Philosophers Problem**, a concurrency challenge used to illustrate resource sharing and synchronization in operating systems. This project is developed in C using **POSIX threads** and **mutexes** to manage concurrent access to shared resources (forks).

---

## 📚 Project Description

A group of philosophers sit at a circular table. Between each pair of philosophers lies a fork. Philosophers must **think**, **eat**, and **sleep** in a loop. To eat, a philosopher must pick up **both** forks to their left and right.

The goal is to manage this process **without deadlocks or data races**, ensuring that all philosophers eat properly or the simulation stops on death due to starvation.

---

## ⚙️ Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

![Philosophers Simulation](media/philosophers.gif)
```

### Arguments

- `number_of_philosophers`: Total number of philosophers (and forks).
- `time_to_die`: Time (in ms) a philosopher can go without eating before dying.
- `time_to_eat`: Time (in ms) a philosopher spends eating.
- `time_to_sleep`: Time (in ms) a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat`: *(optional)* Number of times each philosopher must eat before simulation ends.

---

## 🔄 Simulation Rules

- Each philosopher:
  - Thinks.
  - Picks up **two forks** (left and right) to eat.
  - Eats for `time_to_eat` ms.
  - Releases both forks.
  - Sleeps for `time_to_sleep` ms.
  - Repeats the process.

- If a philosopher **does not eat within `time_to_die` ms**, they die and the simulation ends (unless the optional argument is fulfilled).
- The program must detect and **prevent deadlocks**.
- Actions must be **logged in real-time**, with no more than **10ms delay** from an event like death to its log.

---

## 🪵 Logs Format

Each action is printed to stdout in the following format:

```
<timestamp_in_ms> <philosopher_id> <action>
```

### Example actions:

- `is thinking`
- `has taken a fork`
- `is eating`
- `is sleeping`
- `died`

---

## 🧵 Concurrency Management

- Each philosopher is a **separate thread**.
- Forks are protected by **mutexes** to avoid race conditions.
- A **monitor thread** or timer checks whether any philosopher dies from starvation.
- All shared resources are carefully managed to avoid **data races** and ensure **thread safety**.

---

## 🧠 Philosophers' States

Each philosopher can be in one of three states:
- **Thinking**
- **Eating** *(must hold both forks)*
- **Sleeping**

---
