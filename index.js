import jsonfile from "jsonfile";
import moment from "moment";
import simpleGit from "simple-git";
import { promisify } from "util";

const writeFileAsync = promisify(jsonfile.writeFile);
const path = "./data.json";

// Define the commit date for February 8, 2025 with timezone +05:30
const dateStr = "2025-10-08T00:00:00+05:30";
const formattedDate = moment(dateStr).format("YYYY-MM-DD");

async function makeCommits() {
  const git = simpleGit();

  // Verify that the current directory is a Git repository
  if (!(await git.checkIsRepo())) {
    throw new Error("Not a Git repository!");
  }

  // Create 1 commit on February 8, 2025
  for (let i = 0; i < 1; i++) {
    // Delay 1 second between commits if needed
    if (i > 0) await new Promise((resolve) => setTimeout(resolve, 1000));

    // Create unique file data for each commit
    const data = {
      date: dateStr,
      commit_number: i + 1,
      timestamp: Date.now(),
    };

    console.log(`Creating commit ${i + 1}/1 for ${formattedDate}`);

    try {
      await writeFileAsync(path, data);
      await git.add([path]);
      await git.commit(`Fake commit for ${formattedDate} (commit ${i + 1})`, {
        "--date": dateStr,
      });
    } catch (err) {
      console.error(`Failed at commit ${i + 1}:`, err);
      process.exit(1);
    }
  }

  try {
    // Force push to override remote changes
    await git.push("origin", "main", ["--force"]);
    console.log("Successfully pushed commit to main branch (force pushed)");
  } catch (err) {
    console.error("Final push failed:", err);
    console.log("You may need to force push manually:");
    console.log("git push origin main --force");
  }
}

makeCommits();
