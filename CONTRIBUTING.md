# Contributing to Retro Dungeon Workshop

Thank you for your interest in contributing! This guide will help you through the process.

## Contribution Workflow

### 1. Fork the Repository

Click the "Fork" button at the top right of the repository page to create your own copy.

### 2. Clone Your Fork

```bash
git clone https://github.com/YOUR_USERNAME/retro-dungeon-workshop.git
cd retro-dungeon-workshop
```

### 3. Create a Branch

Create a descriptive branch name based on the issue or feature:

```bash
git checkout -b fix-player-movement-bug
git checkout -b feature-add-potion-items
git checkout -b docs-update-readme
```

### 4. Make Your Changes

- Write clean, readable code following the project's style guidelines
- Add tests for new functionality
- Ensure existing tests pass
- Update documentation if needed

### 5. Commit Your Changes

Use conventional commit messages (see below for details):

```bash
git add .
git commit -m "fix: resolve player movement through walls"
```

### 6. Push to Your Fork

```bash
git push origin fix-player-movement-bug
```

### 7. Open a Pull Request

1. Navigate to your fork on GitHub
2. Click "Compare & pull request"
3. Fill in the PR template with a clear description
4. Link any relevant issues
5. Submit the pull request

## Conventional Commits

All commit messages should follow the conventional commits specification:

```
<type>: <description>
```

### Types

| Type | Description | Example |
|------|-------------|---------|
| `feat` | New feature | `feat: add health potion item` |
| `fix` | Bug fix | `fix: correct player collision detection` |
| `docs` | Documentation only | `docs: update installation instructions` |
| `test` | Adding or modifying tests | `test: add tests for inventory system` |
| `refactor` | Code refactoring without behavior change | `refactor: simplify enemy AI logic` |
| `style` | Code style changes (formatting, etc.) | `style: format combat.cpp` |
| `chore` | Maintenance tasks | `chore: update CMakeLists.txt` |

### Commit Message Guidelines

- Use lowercase for the type
- Keep the description under 72 characters
- Use imperative mood ("add feature" not "added feature")
- Do not end the description with a period

## Code Style

### C++ Standards

- This project uses **C++20** features
- Follow the `.clang-format` configuration in the repository root
- Run formatting before committing:

```bash
cmake --build build --target format
```

### Style Guidelines

- Use `snake_case` for functions and variables
- Use `PascalCase` for classes and types
- Use `UPPER_SNAKE_CASE` for constants
- Keep functions focused and reasonably sized
- Add comments for complex logic
- Use meaningful variable and function names

### Headers

- Place public headers in `include/retro_dungeon/`
- Use include guards: `#pragma once`
- Order includes: standard library, third-party, project headers

## Testing Requirements

### Running Tests

All contributions must pass the existing test suite:

```bash
cmake -B build
cmake --build build
cd build && ctest --output-on-failure
```

### Writing Tests

- Place test files in the `tests/` directory
- Use Catch2 test framework (automatically fetched by CMake)
- Name test files `test_<component>.cpp`
- Use descriptive test case names

Example test structure:

```cpp
#include <catch2/catch_test_macros.hpp>
#include <retro_dungeon/entities/player.hpp>

TEST_CASE("Player takes damage correctly", "[player]") {
    Player player;
    player.set_health(100);
    player.take_damage(20);
    REQUIRE(player.get_health() == 80);
}
```

### Test Coverage

For bug fixes, include a test that verifies the fix:

```cpp
TEST_CASE("Player cannot move through walls", "[player][bugfix]") {
    // Test that reproduces the original bug
    // Assert the expected behavior
}
```

## Common Mistakes to Avoid

### Git Issues

- **Committing directly to main**: Always create a feature branch
- **Large commits**: Break changes into logical, atomic commits
- **Vague commit messages**: Use conventional commits format
- **Ignoring merge conflicts**: Resolve conflicts before opening PR

### Code Issues

- **Failing to format**: Run `clang-format` before committing
- **Skipping tests**: Ensure all tests pass locally
- **Missing tests**: Add tests for new functionality
- **Breaking changes**: Maintain backward compatibility when possible

### Pull Request Issues

- **Missing PR description**: Fill out the template completely
- **No linked issues**: Reference relevant issues with "Fixes #123"
- **Unrelated changes**: One PR should address one issue or feature
- **Draft PRs marked ready**: Use draft status appropriately

## How to Get Help

### Documentation

- Check the README for setup instructions
- Review existing code for patterns and conventions
- Read the test files for usage examples

### Community

- Open a GitHub Discussion for questions
- Ask for clarification on issues you want to work on
- Request a mentor for guidance on complex issues

### Issue Assignment

- Comment on an issue to express interest
- Wait for maintainer assignment before starting work
- Ask questions early if the issue description is unclear

## Pull Request Template

When opening a pull request, include:

```markdown
## Description
Brief description of changes made.

## Related Issue
Fixes #<issue_number>

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Refactoring

## Testing
- [ ] All existing tests pass
- [ ] New tests added for new functionality

## Checklist
- [ ] Code follows style guidelines
- [ ] Commit messages follow conventional commits
- [ ] Documentation updated if needed
```

---

Questions? Open a discussion or ask in the issue comments. We are here to help you succeed!