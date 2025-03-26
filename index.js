import jsonfile from "jsonfile";
import moment from "moment";
import simpleGit from "simple-git";

const path = "./data.json";
const startDate = moment("2025-02-16T00:00:00+05:30");
const endDate = moment("2025-03-07T00:00:00+05:30");

async function makeCommits() {
  const git = simpleGit();
  let current = startDate.clone();

  while (current.isSameOrBefore(endDate)) {
    const dateStr = current.format();
    const commitMessage = `Fake commit for ${current.format("YYYY-MM-DD")}`;

    // Ensure unique file content for each commit
    const data = {
      date: dateStr,
      commit_number: current.diff(startDate, "days") + 1,
    };

    console.log(`Creating commit for ${current.format("YYYY-MM-DD")}`);

    try {
      await jsonfile.writeFile(path, data);
      await git.add([path]);
      await git.commit(commitMessage, { "--date": dateStr });
    } catch (err) {
      console.error(`Failed at ${dateStr}:`, err);
      process.exit(1);
    }

    current.add(1, "day");
  }

  try {
    await git.push("origin", "main");
    console.log("Successfully pushed all commits");
  } catch (err) {
    console.error("Push failed:", err);
  }
}

makeCommits();
