#include <cassert>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <set>
#include <string>

using std::cin, std::cout, std::endl;

// constant values

constexpr int MAX_PROBLEMS = 26;
constexpr int MAX_OPS = 300000;
constexpr int COUNT_SUBMISSION_STATUS = 4;

// type definitions

typedef std::string TeamName;
typedef int TeamId;
typedef int ProblemId;
typedef int SubmissionId;

enum SubmissionStatus {
  ACCEPTED,
  WRONG_ANSWER,
  RUNTIME_ERROR,
  TIME_LIMIT_EXCEEDED,
};

struct Submission {
  SubmissionId id;
  ProblemId problem;
  TeamId team;
  SubmissionStatus status;
  int time;
};

struct ProblemStatus {
  int accepted = -1;
  int acceptedPending = -1;
  int frozen = 0;
  int failCount = 0;
  SubmissionId lastSubmission = -1;
  SubmissionId lastSubmissionByStatus[COUNT_SUBMISSION_STATUS] = { -1, -1, -1, -1 };
};

struct TeamInfo {
  TeamId id;
  TeamName name;
  int rank;
  int frozenRank;
  int countAccepted = 0;
  int countAcceptedPending = 0;
  int penaltyTime = 0;
  int penaltyTimePending = 0;
  SubmissionId lastSubmission = -1;
  SubmissionId lastSubmissionByStatus[COUNT_SUBMISSION_STATUS] = { -1, -1, -1, -1 };
  int lastAcceptedTime = -1;
  int lastAcceptedTimePending = -1;
  ProblemStatus problems[MAX_PROBLEMS];

  bool operator< (const TeamInfo &that) const {
    return name < that.name;
  }
};

enum CompetitionStatus {
  PENDING,
  NORMAL,
  FROZEN,
  ENDED, // not used
};

struct Competition {
 private:
  /// @time O(log n)
  struct cmpTeamByPerformance_ {
    bool operator() (const TeamId &lhsId, const TeamId &rhsId) const {
      const TeamInfo &lhs = Competition::competition.teams[lhsId];
      const TeamInfo &rhs = Competition::competition.teams[rhsId];
      if (lhs.countAccepted != rhs.countAccepted) return lhs.countAccepted > rhs.countAccepted;
      if (lhs.penaltyTime != rhs.penaltyTime) return lhs.penaltyTime < rhs.penaltyTime;
      if (lhs.lastAcceptedTime != rhs.lastAcceptedTime) return lhs.lastAcceptedTime < rhs.lastAcceptedTime;
      int countAccepted = lhs.countAccepted;
      if (countAccepted < 2) return lhsId < rhsId;
      int lhsTimes[MAX_PROBLEMS], rhsTimes[MAX_PROBLEMS];
      for (int i = 0, j = 0; i < countAccepted; ++i) {
        while (lhs.problems[j].accepted < 0) ++j;
        lhsTimes[i] = lhs.problems[j].accepted;
        ++j;
      }
      for (int i = 0, j = 0; i < countAccepted; ++i) {
        while (rhs.problems[j].accepted < 0) ++j;
        rhsTimes[i] = rhs.problems[j].accepted;
        ++j;
      }
      std::sort(lhsTimes, lhsTimes + countAccepted);
      std::sort(rhsTimes, rhsTimes + countAccepted);
      for (int i = countAccepted - 1; i >= 0; --i) {
        if (lhsTimes[i] != rhsTimes[i]) return lhsTimes[i] < rhsTimes[i];
      }
      return lhsId < rhsId;
    }
  };
  /// @time cmpTeamByPerformance_
  struct cmpTeamByPerformanceReversed_ {
    bool operator() (const TeamId &lhs, const TeamId &rhs) const {
      return cmpTeamByPerformance_()(rhs, lhs);
    }
  };
  /// @time O(log n)
  struct cmpSubmissionByTeamAndProblem_ {
    bool operator() (const SubmissionId &lhsId, const SubmissionId &rhsId) const {
      if (lhsId < 0) {
        TeamId lhsTeam = -lhsId - 1;
        const Submission &rhs = Competition::competition.submissions[rhsId];
        return rhs.team >= lhsTeam;
      }
      if (rhsId < 0) {
        TeamId rhsTeam = -rhsId - 1;
        const Submission &lhs = Competition::competition.submissions[lhsId];
        return rhsTeam > lhs.team;
      }
      const Submission &lhs = Competition::competition.submissions[lhsId];
      const Submission &rhs = Competition::competition.submissions[rhsId];
      if (lhs.team != rhs.team) return lhs.team < rhs.team;
      if (lhs.problem != rhs.problem) return lhs.problem < rhs.problem;
      return lhsId < rhsId;
    }
  };
 public:
  static Competition competition;
  std::set<TeamName> teamNames;
  TeamInfo *teams;
  Submission *submissions;
  /// Only for frozen competitions.
  std::set<SubmissionId, cmpSubmissionByTeamAndProblem_> pendingSubmissions;
  /// Only for frozen competitions.
  std::set<TeamId, cmpTeamByPerformanceReversed_> teamsWithFrozenProblems;
  std::set<TeamId> dirtyTeams;
  // ix is for index
  std::unordered_map<TeamName, TeamId> ixTeamIdFromName;
  std::set<TeamId, cmpTeamByPerformance_> ixTeamByPerformance;
  CompetitionStatus status = PENDING;
  int problemCount = -1;
  SubmissionId submissionCount = 0;
};
Competition Competition::competition;

// strings

constexpr char kAddTeamOk[] = "[Info]Add successfully.\n";
constexpr char kAddTeamErrorStarted[] = "[Error]Add failed: competition has started.\n";
constexpr char kAddTeamErrorDuplicate[] = "[Error]Add failed: duplicated team name.\n";
constexpr char kStartOk[] = "[Info]Competition starts.\n";
constexpr char kStartErrorStarted[] = "[Error]Start failed: competition has started.\n";
constexpr char kFlushOk[] = "[Info]Flush scoreboard.\n";
constexpr char kFreezeOk[] = "[Info]Freeze scoreboard.\n";
constexpr char kFreezeErrorFrozen[] = "[Error]Freeze failed: scoreboard has been frozen.\n";
constexpr char kScrollOk[] = "[Info]Scroll scoreboard.\n";
constexpr char kScrollErrorNormal[] = "[Error]Scroll failed: scoreboard has not been frozen.\n";
constexpr char kQueryRankingOk[] = "[Info]Complete query ranking.\n";
constexpr char kQueryRankingErrorNotFound[] = "[Error]Query ranking failed: cannot find the team.\n";
constexpr char kQueryRankingWarningFrozen[] = "[Warning]Scoreboard is frozen. The ranking may be inaccurate until it were scrolled.\n";
constexpr char kQuerySubmissionOk[] = "[Info]Complete query submission.\n";
constexpr char kQuerySubmissionErrorNotFound[] = "[Error]Query submission failed: cannot find the team.\n";
constexpr char kQuerySubmissionWarningNotFound[] = "Cannot find any submission.\n";
constexpr char kEndOk[] = "[Info]Competition ends.\n";
constexpr char kSubmissionStatusAccepted[] = "Accepted";
constexpr char kSubmissionStatusWrongAnswer[] = "Wrong_Answer";
constexpr char kSubmissionStatusRuntimeError[] = "Runtime_Error";
constexpr char kSubmissionStatusTimeLimitExceeded[] = "Time_Limit_Exceed";

// helper functions

[[nodiscard]] inline ProblemId problemIdFromName (const char &problemName) {
  return problemName - 'A';
}

[[nodiscard]] inline const char problemNameFromId (ProblemId id) {
  return id + 'A';
}

[[nodiscard]] inline SubmissionStatus submissionStatusFromString (std::string string) {
  switch (string[0]) {
    case 'A': return ACCEPTED;
    case 'W': return WRONG_ANSWER;
    case 'R': return RUNTIME_ERROR;
    case 'T': return TIME_LIMIT_EXCEEDED;
    default: assert(false);
  }
}

[[nodiscard]] inline const char *submissionStringFromStatus (SubmissionStatus status) {
  switch (status) {
    case ACCEPTED: return kSubmissionStatusAccepted;
    case WRONG_ANSWER: return kSubmissionStatusWrongAnswer;
    case RUNTIME_ERROR: return kSubmissionStatusRuntimeError;
    case TIME_LIMIT_EXCEEDED: return kSubmissionStatusTimeLimitExceeded;
    default: assert(false);
  }
}

[[nodiscard]] inline int penaltyTime (int failCount, int submissionTime) {
  return failCount * 20 + submissionTime;
}

// virtual base classes

class BaseCommand {
 public:
  virtual void execute (Competition &competition) = 0;
};

// commands

/**
 * Adds a team.
 * @time O(log n)
 *
 * Implementation details:
 * 1. Adds the team name into the set of team names.
 */
class AddTeam : BaseCommand {
 public:
  void execute (Competition &competition) {
    TeamName name;
    cin >> name;
    if (competition.status != PENDING) {
      cout << kAddTeamErrorStarted;
      return;
    }
    // 1
    const auto &[ _, success ] = competition.teamNames.insert(name);
    cout << (success ? kAddTeamOk : kAddTeamErrorDuplicate);
  }
};

/**
 * Starts the competition.
 * @time O(n)
 *
 * Implementation details:
 * 1. Creates (`new`) an array of Teams.
 * 2. Creates (`new`) an array of Submissions.
 * 3. For each team name:
 *   1. Inserts a new Team Info object into the array of teams, whose ID is determined by its name.
 *   2. Inserts the Team ID into indices:
 *     1. Index of Team ID from Team Name.
 *     2. Index of Team ID Ordered By Performance.
 * 4. Marks the competition as started.
 */
class Start : BaseCommand {
 public:
  void execute (Competition &competition) {
    std::string _;
    int problemCount;
    cin >> _ >> _ >> _ >> problemCount;
    if (competition.status != PENDING) {
      cout << kStartErrorStarted;
      return;
    }
    competition.problemCount = problemCount;
    competition.teams = new TeamInfo[competition.teamNames.size()]; // 1
    competition.submissions = new Submission[MAX_OPS]; // 2
    TeamId id = 0;
    for (const TeamName &name : competition.teamNames) {
      TeamInfo info {
        .id = id,
        .name = name,
        .rank = id + 1, // rank is 1-based while id is 0-based
      };
      competition.teams[id] = info; // 3.1
      competition.ixTeamIdFromName[name] = id; // 3.2.1
      competition.ixTeamByPerformance.insert(id); // 3.2.2
      ++id;
    }
    competition.status = NORMAL; // 4
    cout << kStartOk;
  }
};

/**
 * Inserts a submission into pending state.
 * @time O(log n)
 *
 * Implementation details:
 * 1. Inserts a new Submission object into the Set of Submissions.
 * 2. Updates the Last Submission Indices.
 * 3. If the team already has Accepted submissions for this Problem, then
 *   1. Returns.
 * 4. If the status of competition is Frozen, then
 *   1. Marks the problem as Frozen.
 *   2. Inserts the Submission ID into the Set of Pending Problems.
 *   3. Inserts the corresponding Team ID into the Set of Teams With Frozen Problems.
 * 5. If the status of competition is Normal, then
 *   1. If the submission status is Accepted, then
 *     1. Marks the problem as Accepted.
 *     2. Increases the Pending Accepted Problem Counter.
 *     3. Adds Pending Penalty Time.
 *     4. Inserts the Team ID into the Set of Dirty Teams.
 *     5. Updates the Pending Last Submission Time.
 *   2. If the submission status is not Accepted, then
 *     1. Increases the Unaccepted Submissions Counter.
 */
class Submit : BaseCommand {
 public:
  void execute (Competition &competition) {
    char problemName;
    std::string _, sSubmitStatus;
    TeamName teamName;
    int time;
    cin >> problemName >> _ >> teamName >> _ >> sSubmitStatus >> _ >> time;
    SubmissionId id = competition.submissionCount++;
    Submission &submission = competition.submissions[id];
    // 1
    submission.id = id;
    submission.problem = problemIdFromName(problemName);
    submission.status = submissionStatusFromString(sSubmitStatus);
    submission.team = competition.ixTeamIdFromName[teamName];
    submission.time = time;
    TeamInfo &team = competition.teams[submission.team];
    // 2
    team.lastSubmission = id;
    team.lastSubmissionByStatus[submission.status] = id;
    team.problems[submission.problem].lastSubmission = id;
    team.problems[submission.problem].lastSubmissionByStatus[submission.status] = id;
    // 3
    if (
      team.problems[submission.problem].accepted > -1 ||
      team.problems[submission.problem].acceptedPending > -1
    ) return;
    // 4
    if (competition.status == FROZEN) {
      ++(team.problems[submission.problem].frozen); // 4.1
      competition.pendingSubmissions.insert(id); // 4.2
      competition.teamsWithFrozenProblems.insert(submission.team); // 4.3
    } else { // 5
      if (submission.status == ACCEPTED) { // 5.1
        team.problems[submission.problem].acceptedPending = submission.time; // 5.1.1
        ++(team.countAcceptedPending); // 5.1.2
        // 5.1.3
        team.penaltyTimePending += penaltyTime(team.problems[submission.problem].failCount, submission.time);
        competition.dirtyTeams.insert(submission.team); // 5.1.4
        team.lastAcceptedTimePending = time; // 5.1.5
      } else { // 5.2
        ++(team.problems[submission.problem].failCount); // 5.2.1
      }
    }
  }
};

/**
 * Flushes the scoreboard.
 * @time O(m log n) where m is the number of Dirty Teams
 *
 * Implementation details:
 * 1. If there are no Dirty Teams:
 *   1. Returns.
 * 2. For each Dirty Team:
 *   1. Erases the Team from the Index of Teams Ordered By Performance.
 *   2. Sets the Accepted Problem Counter, Last Accepted Time and Penalty Time according to their Pending variants.
 *   3. Clears Pending Accepted Problem Counter, Pending Last Accepted Time and Pending Penalty Time.
 *   4. Inserts the Team back to the Index of Teams Ordered By Performance.
 * 3. Empties the Set of Dirty Teams.
 * 4. For each Team:
 *   1. Sets its Rank.
 */
class Flush : BaseCommand {
 public:
  void executeSilently (Competition &competition) {
    if (competition.status == FROZEN) {
      for (int i = 0; i < competition.teamNames.size(); ++i) {
        TeamInfo &team = competition.teams[i];
        team.frozenRank = team.rank;
      }
    }
    if (competition.dirtyTeams.size() == 0) return; // 1
    for (const TeamId &teamId : competition.dirtyTeams) { // 2
      competition.ixTeamByPerformance.erase(teamId); // 2.1
      // 2.2
      TeamInfo &team = competition.teams[teamId];
      team.countAccepted += team.countAcceptedPending;
      if (team.lastAcceptedTimePending > -1) team.lastAcceptedTime = team.lastAcceptedTimePending;
      team.penaltyTime += team.penaltyTimePending;
      for (int i = 0; i < competition.problemCount; ++i) {
        if (team.problems[i].acceptedPending > -1) {
          team.problems[i].accepted = team.problems[i].acceptedPending;
          team.problems[i].acceptedPending = -1;
        }
      }
      // 2.3
      team.countAcceptedPending = 0;
      team.lastAcceptedTimePending = -1;
      team.penaltyTimePending = 0;
      competition.ixTeamByPerformance.insert(teamId); // 2.4
    }
    competition.dirtyTeams.clear(); // 3
    int rank = 0;
    for (const TeamId &teamId : competition.ixTeamByPerformance) { // 4
      competition.teams[teamId].rank = ++rank; // 4.1
    }
    assert(competition.ixTeamByPerformance.size() == competition.teamNames.size());
  }
  void execute (Competition &competition) {
    executeSilently(competition);
    cout << kFlushOk;
  }
};

/**
 * Flushes then Freezes the scoreboard.
 * @time O(n) + Flush
 *
 * Implementation details:
 * 1. For each Team,
 *   1. Sets Frozen Rank to Rank.
 * 2. Calls Flush.
 * 3. Marks the competition as Frozen.
 */
class Freeze : BaseCommand {
 public:
  void execute (Competition &competition) {
    if (competition.status == FROZEN) {
      cout << kFreezeErrorFrozen;
      return;
    }
    for (int i = 0; i < competition.teamNames.size(); ++i) { // 1
      TeamInfo &team = competition.teams[i];
      team.frozenRank = team.rank; // 1.1
    }
    Flush().executeSilently(competition); // 2
    competition.status = FROZEN; // 3
    cout << kFreezeOk;
  }
};

/**
 * Scrolls the scoreboard.
 * @time O(n log n)
 *
 * Implementation details:
 * 1. Prints out the current Scoreboard.
 * 2. Lets the Team Iterator be the first in the Set of Teams with Frozen Problems.
 * 3. Loop,
 *   1. Finds the Team' of the next Performance.
 *   2. Lets the Submission Iterator be the first Pending Submission of that Team.
 *   3. Loop,
 *     0. Sets the frozen count of the problem to 0.
 *     1. If the Status is Accepted, then
 *       1. Increases the Team Iterator.
 *       2. Removes the Team from the Set of Teams with Frozen Problems.
 *       3. Removes all submissions of this Team and this Problem from the Set of Pending Submissions.
 *       4. Sets the Submission Iterator to the iterator returned in 3.3.1.3.
 *       5. Erases the Team from the Index of Teams Ordered by Performance.
 *       6. Marks the problem as Accepted.
 *       7. Increases the Accepted Problem Counter.
 *       8. Adds Penalty Time.
 *       9. Updates the Last Submission Time.
 *       10. Inserts the Team to the Index of Teams Ordered By Performance.
 *       11. If the Team'' of the next Performance is not Team', i.e. the ranking has changed, then
 *         1. Prints out info of ranking change.
 *       12. If there are no Pending Submissions for that Team, then
 *         1. Goes to 3.4.
 *       13. Inserts the Team back to the Set of Teams with Frozen Problems.
 *       14. Increases the iterator returned in 3.3.1.13.
 *       15. If the iterator in 3.3.1.14 is the Team Iterator, i.e. the next Team to scroll is still this Team, then
 *         1. Decreases the Team Iterator.
 *         2. Continues.
 *       16. Goes to 3.4.
 *     2. If the submission status is not Accepted, then
 *       1. Increases the Unaccepted Submissions Counter.
 *       2. Removes the Submission from the Set of Pending Submissions.
 *       3. Sets the Submission Iterator to the iterator returned in 3.3.2.2.
 *       4. If there the Submission of the Submission Iterator is Null or does not belong to the Team, then
 *         1. Removes the Team from the Set of Teams with Frozen Problems.
 *         2. Sets the Team Iterator to the iterator returned in 3.3.2.4.1.
 *         3. Breaks.
 *       5. Continues.
 *   4. If the Team Iterator is Null, then
 *     1. Breaks.
 * 4. Sets the Status of the Competition to Normal.
 * 5. For each Team:
 *   1. Sets its Rank.
 * 6. Prints out the current Scoreboard.
 */
class Scroll : BaseCommand {
 private:
  inline void printProblem_ (const ProblemStatus &problem) {
    if (problem.accepted > -1) {
      cout << '+';
      if (problem.failCount != 0) cout << problem.failCount;
    } else if (!problem.frozen) {
      if (problem.failCount == 0) {
        cout << '.';
      } else {
        cout << '-' << problem.failCount;
      }
    } else {
      if (problem.failCount == 0) {
        cout << '0';
      } else {
        cout << '-' << problem.failCount;
      }
      cout << '/' << problem.frozen;
    }
  }
  inline void printTeam_ (const Competition &competition, const TeamInfo &team) {
    cout << team.name << ' ' << team.rank << ' ' << team.countAccepted << ' ' << team.penaltyTime;
    for (ProblemId i = 0; i < competition.problemCount; ++i) {
      cout << ' ';
      printProblem_(team.problems[i]);
    }
    cout << '\n';
  }
  inline void printScoreboard_ (const Competition &competition) {
    for (const TeamId &teamId : competition.ixTeamByPerformance) {
      printTeam_(competition, competition.teams[teamId]);
    }
  }
  inline void printRankingChange_ (const TeamInfo &team, const TeamInfo &nextTeam) {
    cout << team.name << ' ' << nextTeam.name << ' ' << team.countAccepted << ' ' << team.penaltyTime << '\n';
  }
 public:
#ifdef DEBUG
  inline void printScoreboard (const Competition &competition) {
    printScoreboard_(competition);
  }
#endif
  void execute (Competition &competition) {
    if (competition.status == NORMAL) {
      cout << kScrollErrorNormal;
      return;
    }
    cout << kScrollOk;

    printScoreboard_(competition); // 1
    if (competition.teamsWithFrozenProblems.size() == 0) {
      competition.status = NORMAL;
      printScoreboard_(competition);
      return;
    }
    auto teamIt = competition.teamsWithFrozenProblems.begin(); // 2
    while (true) { // 3
      // 3.1
      TeamId currentTeamId = *teamIt;
      TeamInfo &currentTeam = competition.teams[currentTeamId];
#ifdef DEBUG_SCROLL
      cout << currentTeam.name << endl;
#endif
      auto nextPerfTeamIt = competition.ixTeamByPerformance.upper_bound(currentTeamId);
      // 3.2
      auto submissionIt = competition.pendingSubmissions.lower_bound(-currentTeamId - 1);
      while (true) { // 3.3
        Submission &currentSubmission = competition.submissions[*submissionIt];
        currentTeam.problems[currentSubmission.problem].frozen = 0; // 3.3.0
#ifdef DEBUG_SCROLL
        cout << currentSubmission.problem << endl;
#endif
        if (currentSubmission.status == ACCEPTED) { // 3.3.1
          ++teamIt; // 3.3.1.1
          competition.teamsWithFrozenProblems.erase(currentTeamId); // 3.3.1.2
          const ProblemId currentProblem = currentSubmission.problem;
          const int currentSubmissionTime = currentSubmission.time;
          // 3.3.1.3, 3.3.1.4
          while (true) {
            submissionIt = competition.pendingSubmissions.erase(submissionIt);
            bool noMorePendingSubmissions = submissionIt == competition.pendingSubmissions.end();
            if (noMorePendingSubmissions) break;
            Submission &nextPendingSubmission = competition.submissions[*submissionIt];
            bool nextPendingSubmissionDoesNotBelongToTeam = nextPendingSubmission.team != currentTeamId;
            if (nextPendingSubmissionDoesNotBelongToTeam) break;
            bool nextPendingSubmissionIsNotCurrentProblem = nextPendingSubmission.problem != currentProblem;
            if (nextPendingSubmissionIsNotCurrentProblem) break;
          }
          competition.ixTeamByPerformance.erase(currentTeamId); // 3.3.1.5
          currentTeam.problems[currentProblem].accepted = currentSubmission.time; // 3.3.1.6
          ++(currentTeam.countAccepted); // 3.3.1.7
          currentTeam.penaltyTime += penaltyTime(currentTeam.problems[currentProblem].failCount, currentSubmissionTime); // 3.3.1.8
          if (currentTeam.lastAcceptedTime < currentSubmissionTime) { // 3.3.1.9
            currentTeam.lastAcceptedTime = currentSubmissionTime;
          }
          competition.ixTeamByPerformance.insert(currentTeamId); // 3.3.1.10
          assert(competition.ixTeamByPerformance.size() == competition.teamNames.size());
          // 3.3.1.11
          auto nextPerfTeamNewIt = competition.ixTeamByPerformance.upper_bound(currentTeamId);
          if (nextPerfTeamNewIt != nextPerfTeamIt) { // 3.3.1.11
#ifdef DEBUG_18
            if (currentTeam.name == "Team_WPRTRZSQ" && currentTeam.countAccepted == 21 && currentTeam.penaltyTime == 75279) {
              const auto f = [] (const TeamInfo &team) -> void {
                int countAccepted = team.countAccepted;
                int times[MAX_PROBLEMS];
                for (int i = 0, j = 0; i < countAccepted; ++i) {
                  while (team.problems[j].accepted < 0) ++j;
                  times[i] = team.problems[j].accepted;
                  ++j;
                }
                std::sort(times, times + countAccepted);
                std::cerr << team.name << ' ';
                for (const int &x : times) std::cerr << x << ' ';
                std::cerr << endl;
              };
              f(currentTeam);
              f(competition.teams[3779]);
              f(competition.teams[842]);
              cout << "bp";
            }
#endif
            printRankingChange_(currentTeam, competition.teams[*nextPerfTeamNewIt]); // 3.3.1.11.1
          }
          if (
            submissionIt == competition.pendingSubmissions.end() ||
            competition.submissions[*submissionIt].team != currentTeamId
          ) { // 3.3.1.12
            goto breakNextTeam; // 3.3.1.12.1
          }
          auto &&it = competition.teamsWithFrozenProblems.insert(currentTeamId).first; // 3.3.1.13
          ++it; // 3.3.1.14
          if (it == teamIt) { // 3.3.1.15
            --teamIt; // 3.3.1.15.1
            continue; // 3.3.1.15.2
          }
          goto breakNextTeam; // 3.3.1.16
        } else { // 3.3.2
          ++(currentTeam.problems[currentSubmission.problem].failCount); // 3.3.2.1
          submissionIt = competition.pendingSubmissions.erase(submissionIt); // 3.3.2.2, 3.3.2.3
          if (
            submissionIt == competition.pendingSubmissions.end() ||
            competition.submissions[*submissionIt].team != currentTeamId
          ) { // 3.3.2.4
            teamIt = competition.teamsWithFrozenProblems.erase(teamIt); // 3.3.2.4.1, 3.3.2.4.2
            break; // 3.3.2.4.3
          }
          continue; // 3.3.2.5
        }
      }
      breakNextTeam:
      if (teamIt == competition.teamsWithFrozenProblems.end()) break; // 3.4.1
    }
    competition.status = NORMAL; // 4
    // 5
    int rank = 0;
    for (const TeamId &teamId : competition.ixTeamByPerformance) {
      competition.teams[teamId].rank = ++rank; // 5.1
    }
    printScoreboard_(competition); // 6
  }
};

/**
 * Queries the ranking of a given Team.
 * @time O(log n)
 *
 * Implementation details:
 * 1. Finds the Team Info of the Team.
 * 2. If the Status of the Competition is Frozen, then
 *   1. Prints the Team's Frozen Rank.
 * 3. If the Status of the Competition is Normal, then
 *   1. Prints the Team's Rank.
 */
class QueryRanking : BaseCommand {
 private:
  inline void printRank_ (const std::string &teamName, const int rank) {
    // TODO: does C++ have template literals?
    cout << teamName << " NOW AT RANKING " << rank << '\n';
  }
 public:
  void execute (Competition &competition) {
    TeamName teamName;
    cin >> teamName;
    if (competition.ixTeamIdFromName.count(teamName) == 0) {
      cout << kQueryRankingErrorNotFound;
      return;
    }
    cout << kQueryRankingOk;
    TeamId teamId = competition.ixTeamIdFromName[teamName];
    TeamInfo &team = competition.teams[teamId]; // 1
    if (competition.status == FROZEN) { // 2
      cout << kQueryRankingWarningFrozen;
      printRank_(teamName, team.frozenRank); // 2.1
    } else { // 3
      printRank_(teamName, team.rank); // 3.1
    }
#ifdef DEBUG_QR
    Scroll().printScoreboard(competition);
#endif
  }
};

/**
 * Queries a submission with given constraints.
 * @time O(log n)
 *
 * Implementation details:
 * 1. Finds the Team Info.
 * 2. Finds the Submission ID of the Query.
 * 3. Prints the Submission.
 */
class QuerySubmission : BaseCommand {
 public:
  void execute (Competition &competition) {
    TeamName teamName;
    cin >> teamName;
    if (competition.ixTeamIdFromName.count(teamName) == 0) {
      std::string _;
      cin >> _ >> _ >> _ >> _;
      cout << kQuerySubmissionErrorNotFound;
      return;
    }
    TeamId teamId = competition.ixTeamIdFromName[teamName];
    TeamInfo &team = competition.teams[teamId]; // 1
    for (int i = 0; i < 15; ++i) cin.get();
    char problemName = cin.get();
    ProblemId problem = problemIdFromName(problemName);
    if (cin.peek() != ' ') {
      problem = -1;
      cin.get();
      cin.get();
    }
    for (int i = 0; i < 12; ++i) cin.get();
    std::string statusName;
    cin >> statusName;
    int status = (statusName[1] == 'L') ? -1 : submissionStatusFromString(statusName);
    SubmissionId submissionId;
    // 2
    if (problem < 0 && status < 0) {
      submissionId = team.lastSubmission;
    } else if (problem < 0) {
      submissionId = team.lastSubmissionByStatus[status];
    } else if (status < 0) {
      submissionId = team.problems[problem].lastSubmission;
    } else {
      submissionId = team.problems[problem].lastSubmissionByStatus[status];
    }
    // 3
    cout << kQuerySubmissionOk;
    if (submissionId < 0) {
      cout << kQuerySubmissionWarningNotFound;
    } else {
      const Submission &submission = competition.submissions[submissionId];
      cout << teamName << ' ' << problemNameFromId(submission.problem) << ' ' << submissionStringFromStatus(submission.status) << ' ' << submission.time << '\n';
    }
  }
};

/**
 * Ends the competition and exits the program.
 * @time O(1)
 *
 * Implementation details:
 * 1. Deletes the array of Teams.
 * 2. Deletes the array of Submissions.
 * 3. Exits the program.
 */
class End : BaseCommand {
 public:
  void execute (Competition &competition) {
    cout << kEndOk;
    delete[] competition.teams; // 1
    delete[] competition.submissions; // 2
    exit(0); // 3
  }
};

int main () {
#ifdef ONLINE_JUDGE
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
#endif
#ifdef DEBUG_VSCODE
  freopen("../../ICPC-Management-System-2021/18/18.in", "r", stdin);
  freopen("/dev/null", "w", stdout);
#endif
#ifdef DEBUG_CMD
  int i = 0;
#endif

  while (true) {
    std::string command;
    cin >> command;

#ifdef DEBUG_CMD
    cout << i++ << ' ' << command << endl;
#endif

    const char first = command[0];
    const char second = command[1];
    switch (first) {
      case 'A': AddTeam().execute(Competition::competition); break;
      case 'S': switch (second) {
        case 'T': Start().execute(Competition::competition); break;
        case 'U': Submit().execute(Competition::competition); break;
        case 'C': Scroll().execute(Competition::competition); break;
        default: assert(false);
      }
      break;
      case 'F': switch (second) {
        case 'L': Flush().execute(Competition::competition); break;
        case 'R': Freeze().execute(Competition::competition); break;
        default: assert(false);
      }
      break;
      case 'Q': {
        const char seventh = command[6];
        switch (seventh) {
          case 'R': QueryRanking().execute(Competition::competition); break;
          case 'S': QuerySubmission().execute(Competition::competition); break;
          default: assert(false);
        }
      }
      break;
      case 'E': End().execute(Competition::competition); break;
      default: assert(false);
    }
  }
}
