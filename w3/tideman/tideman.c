#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle_check(int end, int start);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        // if vote is the same as a candidate
        if (strcmp(name, candidates[i]) == 0)
        {
            // set that rank to that candidate
            ranks[rank] = i;
            printf("%i\n", ranks[rank]);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // scan through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        int place1 = 0;
        // get candidate 1 rank
        for (int n = 0; n < candidate_count; n++)
        {
            if(ranks[n] == i)
            {
                place1 = n;
                // printf("first candidate's rank = %i\n", place1);
                break;
            }
        }
        // compare them to every candidate
        for (int j = 0; j < candidate_count; j++)
        {
            int place2 = 0;
            //get candidate 2 rank
            for (int m = 0; m < candidate_count; m++)
            {
                if(ranks[m] == j)
                {
                    place2 = m;
                    // printf("second candidate's rank = %i\n", place2);
                    break;
                }
            }
            // if candidate 1 is ranked higher than candidate 2 (lower rank)
            if (place1 < place2)
            {
                preferences[i][j] = preferences[i][j] + 1;

            }
        }
    }
    // increase preferences for each pair by 1
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // for every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // against every candidate
        for (int j = 0; j < candidate_count; j++)
        {
            // if candidate 1 is prefered over candidate 2 more than candidate 2 over candidate 1
            if (preferences[i][j] > preferences[j][i])
            {
                //add pair to pairs array
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // update pair count
                pair_count = pair_count + 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // scan through all pairs
    for (int i = 0; i < pair_count; i++)
    {
        // compare to every pair
        for (int j = 0; j < pair_count; j++)
        {
            // compare strength of pairs
            int edge1 = preferences[pairs[j].winner][pairs[j].loser];
            int edge2 = preferences[pairs[j+1].winner][pairs[j+1].loser];
            // if out of order
            if (edge1 < edge2)
            {
                // save lower pair
                pair stored = pairs[j];
                // reorder
                pairs[j] = pairs[j+1];
                // replace lower pair
                pairs[j+1] = stored;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    //cycle through pairs
    for (int i = 0; i < pair_count; i++)
    {
        //check if pair causes cycle
        if(!cycle_check(pairs[i].loser, pairs[i].winner))
        {
            //lock pair
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // cycle through winning candidates
    for (int i = 0; i < candidate_count; i++)
    {
        int falses = 0;
        // cycle through losing candidates
        for (int j = 0; j < candidate_count; j++)
        {
            // check if pair is open
            if (locked[j][i] == false)
            {
                falses = falses + 1;
                // check if open for all candidates
                if (falses == candidate_count)
                {
                    // candidate has no arrows towards themselves, print as winner
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}

bool cycle_check(int end, int start)
{
    // immediately return true when cycle completed
    if (end == start)
    {
        return true;
    }
    // go through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if(locked[end][i])
        {
            if(cycle_check(i, start))
            {
                return true;
            }
        }
    }
    return false;
}