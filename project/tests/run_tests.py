#!/usr/bin/env python3
import subprocess
from pathlib import Path

root = Path(__file__).resolve().parent.parent
passed = 0
failed = 0

def check(name, command, expected=None):
    global passed, failed
    result = subprocess.run(command, cwd=root, capture_output=True, text=True)
    if result.returncode == 0 and (expected is None or result.stdout == expected.read_text()):
        passed += 1
    else:
        failed += 1
        print('FAIL:', name)
        print(result.stderr or result.stdout[:500])

check('unit tests', ['./tests/unit'])
for scenario in sorted((root / 'scenarios').glob('*.txt')):
    if scenario.name.endswith('.expected.txt'):
        continue
    for flag, suffix in [([], '.expected'), (['--report'], '.report.expected')]:
        expected = scenario.with_suffix(suffix)
        if expected.exists():
            check(scenario.name + suffix, ['./gate', str(scenario), *flag], expected)
print(f'Tests: {passed} passed, {failed} failed')
raise SystemExit(bool(failed))
