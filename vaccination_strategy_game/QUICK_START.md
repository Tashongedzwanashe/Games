# Quick Start Guide - Contain the Spread

## 🚀 Get Started in 3 Steps

### 1. Compile the Game

**Windows:**

```bash
compile.bat
```

**Linux/macOS:**

```bash
make
```

### 2. Run the Game

```bash
./contain_the_spread.exe  # Windows
./contain_the_spread      # Linux/macOS
```

### 3. Play!

- Follow the prompts to configure your simulation
- Choose a vaccination strategy (1-5)
- Watch the disease spread and vaccinate strategically
- Try to minimize your total cost!

## 🎯 Recommended First Game

For your first game, try these settings:

- **Grid Size**: 15x15
- **Initial Infection Rate**: 3%
- **Infection Probability**: 0.15
- **Recovery Time**: 3 turns
- **Vaccination Cost**: $10
- **Infection Penalty**: $50
- **Max Vaccinations**: 5 per turn
- **Strategy**: 1 (Manual) - for learning

## 🧪 Test the Game

Run the automated test:

```bash
python test_game.py
```

Compare all strategies:

```bash
python demo_strategies.py
```

## 📚 Learn More

- **README.md** - Complete game documentation
- **documentation.md** - Technical implementation details
- **Makefile** - Build options and targets

## 🎮 Strategies Explained

1. **Manual** - You choose where to vaccinate
2. **Random** - Computer vaccinates randomly
3. **Ring** - Vaccinates around infected areas
4. **High-Density** - Targets crowded areas
5. **Greedy** - Vaccinates highest-risk areas

## 🏆 Scoring

- **Gold**: < $1000
- **Silver**: < $2000
- **Bronze**: < $3000
- **Needs Improvement**: ≥ $3000

---

**Have fun containing the spread!** 🦠💉
