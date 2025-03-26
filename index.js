import jsonfile from "jsonfile";
import moment from "moment";
import simpleGit from "simple-git";
import { promisify } from "util";

// Promisify jsonfile.writeFile
const writeFileAsync = promisify(jsonfile.writeFile);
const path = "./data.json";

// Define the dates array
const dates = ["2023-11-05T00:00:00+05:30"];

async function makeCommits() {
  const git = simpleGit();

  // Verify Git repository
  if (!(await git.checkIsRepo())) {
    throw new Error("Not a Git repository!");
  }

  for (let i = 0; i < dates.length; i++) {
    // Add 1-second delay between commits
    if (i > 0) await new Promise((resolve) => setTimeout(resolve, 1000));

    const dateStr = dates[i];
    const formattedDate = moment(dateStr).format("YYYY-MM-DD");

    const data = {
      date: dateStr,
      commit_number: i + 1,
      timestamp: Date.now(),
    };

    console.log(`Creating commit ${i + 1}/${dates.length}: ${formattedDate}`);

    try {
      // Use the promisified writeFile function
      await writeFileAsync(path, data);
      await git.add([path]);
      await git.commit(`Fake commit for ${formattedDate}`, {
        "--date": dateStr,
      });
    } catch (err) {
      console.error(`Failed at ${dateStr}:`, err);
      process.exit(1);
    }
  }

  try {
    await git.push("origin", "main");
    console.log("Successfully pushed all commits to main branch");
  } catch (err) {
    console.error("Final push failed:", err);
    console.log("You may need to force push:");
    console.log("git push origin main --force");
  }
}

makeCommits();
