import os
import sys
import subprocess
from src.utils.logger import Logger

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "../src")))

def pytest_sessionfinish(session, exitstatus):
    cleanup_script = os.path.abspath(os.path.join(os.path.dirname(__file__), "../cleanup.sh"))
    if os.path.exists(cleanup_script):
        Logger.log("INFO", f"Running cleanup script: {cleanup_script}")
        try:
            subprocess.run(["bash", cleanup_script], check=True)
            Logger.log("INFO", "Cleanup script completed successfully")
        except subprocess.CalledProcessError as e:
            Logger.error(f"Error running cleanup script: {e}")
    else:
        Logger.error(f"Cleanup script not found: {cleanup_script}")