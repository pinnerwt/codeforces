#!/usr/bin/env python3
"""
Competitive Companion listener.
Receives parsed problems and saves test cases in cf-tool format.

Usage:
    python3 listen.py              # listen once (single problem)
    python3 listen.py --contest    # listen for a full contest (keeps listening until Ctrl+C)

Directory structure created:
    <contest_id>/<problem_letter>/in1.txt, ans1.txt, in2.txt, ans2.txt, ...
"""

import http.server
import json
import os
import re
import shutil
import sys

PORT = 10043  # Competitive Companion custom port

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
TEMPLATE_PATH = os.path.join(BASE_DIR, 'template.cpp')


def parse_url(url):
    """Extract contest id and problem letter from a Codeforces URL."""
    # Handles:
    #   /contest/1234/problem/A
    #   /problemset/problem/1234/A
    #   /gym/1234/problem/A
    #   /group/xxx/contest/1234/problem/A
    m = re.search(r'/(?:contest|gym)/(\d+)/problem/(\w+)', url)
    if m:
        return m.group(1), m.group(2).upper()
    m = re.search(r'/problemset/problem/(\d+)/(\w+)', url)
    if m:
        return m.group(1), m.group(2).upper()
    return None, None


def save_problem(data):
    """Save a parsed problem's test cases to disk."""
    url = data.get('url', '')
    name = data.get('name', '')
    contest_id, letter = parse_url(url)

    if not contest_id or not letter:
        # Fallback: use group name and problem name
        group = data.get('group', 'unknown')
        gm = re.search(r'(\d+)', group)
        contest_id = gm.group(1) if gm else 'unknown'
        letter = name[0].upper() if name else 'X'

    problem_dir = os.path.join(BASE_DIR, contest_id, letter.lower())
    os.makedirs(problem_dir, exist_ok=True)

    tests = data.get('tests', [])
    for i, test in enumerate(tests, 1):
        in_path = os.path.join(problem_dir, f'in{i}.txt')
        ans_path = os.path.join(problem_dir, f'ans{i}.txt')
        with open(in_path, 'w') as f:
            f.write(test.get('input', ''))
        with open(ans_path, 'w') as f:
            f.write(test.get('output', ''))

    # Copy C++ template if it exists and sol.cpp doesn't already exist
    sol_path = os.path.join(problem_dir, 'sol.cpp')
    if os.path.isfile(TEMPLATE_PATH) and not os.path.isfile(sol_path):
        shutil.copy2(TEMPLATE_PATH, sol_path)
        print(f"  Copied template.cpp -> {contest_id}/{letter.lower()}/sol.cpp")

    # Copy test.sh if it exists and isn't already in the problem dir
    test_sh_src = os.path.join(BASE_DIR, 'test.sh')
    test_sh_dst = os.path.join(problem_dir, 'test.sh')
    if os.path.isfile(test_sh_src) and not os.path.isfile(test_sh_dst):
        shutil.copy2(test_sh_src, test_sh_dst)
        print(f"  Copied test.sh -> {contest_id}/{letter.lower()}/test.sh")

    print(f"  Saved {len(tests)} test(s) to {contest_id}/{letter.lower()}/")
    return contest_id, letter


class Handler(http.server.BaseHTTPRequestHandler):
    problems_received = 0

    def do_POST(self):
        length = int(self.headers['Content-Length'])
        body = self.rfile.read(length)
        data = json.loads(body)

        self.send_response(200)
        self.end_headers()

        name = data.get('name', '?')
        url = data.get('url', '')
        print(f"[+] Received: {name}")
        print(f"    URL: {url}")
        save_problem(data)
        Handler.problems_received += 1

    def log_message(self, format, *args):
        pass  # suppress default logging


def main():
    contest_mode = '--contest' in sys.argv

    server = http.server.HTTPServer(('127.0.0.1', PORT), Handler)
    print(f"Listening on port {PORT}...")
    print(f"Add {PORT} to Competitive Companion custom ports in extension settings.")
    if contest_mode:
        print("Contest mode: listening until Ctrl+C")
    else:
        print("Single mode: will exit after first problem (use --contest for multiple)")
    print()

    try:
        if contest_mode:
            server.serve_forever()
        else:
            server.handle_request()
    except KeyboardInterrupt:
        pass

    print(f"\nDone. Received {Handler.problems_received} problem(s).")


if __name__ == '__main__':
    main()
