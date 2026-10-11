using System;
using System.Collections.Generic;
using System.Numerics;
using System.Runtime.Intrinsics;
using System.Text;
using static System.Runtime.InteropServices.JavaScript.JSType;
using System.Linq;
using System.Collections;

namespace CS_practice
{

    public class ListNode
    {
        public int val;
        public ListNode next;
        public ListNode(int val = 0, ListNode next = null)
        {
            this.val = val;
            this.next = next;
        }
    }

    namespace task_1344
    {
        /*
		* https://leetcode.com/problems/angle-between-hands-of-a-clock/description/
		*/
        public class Solution
        {
			public double AngleClock(int hour, int minutes)
            {
                double angle = minutes * 6 - (hour % 12) * 30 - minutes / 2.0;
                if (angle < 0)
                    angle += 360;
                if (angle > 180)
                    angle = 360 - angle;
                return angle;
            }
        };
    }

    namespace task_1406
    {
        /*
		* https://leetcode.com/problems/stone-game-iii/description/
		*/
        public class Solution
        {
            public string StoneGameIII(int[] stoneValue)
            {
                int size = stoneValue.Length;
                int[] dp = new int[size];

                for (int i = size - 1; i >= 0; i--)
                {
                    int take_1 = Int32.MinValue, take_2 = Int32.MinValue, take_3 = Int32.MinValue;
                    take_1 = stoneValue[i];
                    if (i + 1 < size)
                    {
                        take_2 = take_1 + stoneValue[i + 1];
                        take_1 -= dp[i + 1];
                    }
                    if (i + 2 < size)
                    {
                        take_3 = take_2 + stoneValue[i + 2];
                        take_2 -= dp[i + 2];
                    }
                    if (i + 3 < size)
                    {
                        take_3 -= dp[i + 3];
                    }

                    dp[i] = Math.Max(take_1, Math.Max(take_2, take_3));
                }
                return dp[0] > 0 ? "Alice" : dp[0] < 0 ? "Bob" : "Tie";
            }
        };
    }

    namespace task_1732
    {
        /*
		* https://leetcode.com/problems/find-the-highest-altitude/description/
		*/
        public class Solution
        {
            public int LargestAltitude(int[] gain)
            {
                int max_alt = 0, alt = 0;
                foreach (var value in gain)
                {
                    alt += value;
                    max_alt = Math.Max(max_alt, alt);
                }
                return max_alt;
            }
        };
    }

    namespace task_2095
    {
        /*
		* https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/description/
		*/
        public class Solution
        {
            public ListNode DeleteMiddle(ListNode head)
            {
                if (head.next == null)
                    return null;
                ListNode ptr1 = head;
                ListNode ptr2 = head.next.next;
                while (ptr2 != null)
                {
                    ptr2 = ptr2.next;
                    if (ptr2 != null)
                        ptr2 = ptr2.next;
                    else
                        break;
                    ptr1 = ptr1.next;
                }
                ptr1.next = ptr1.next.next;
                return head;
            }
        }
    }

    namespace task_2126
    {
        /*
		* https://leetcode.com/problems/destroying-asteroids/description/
		*/
        class Solution
        {
            public bool AsteroidsDestroyed(int mass, int[] asteroids)
            {
                Array.Sort(asteroids);
                long sum = mass;
                foreach (int asteroid in asteroids)
                {
                    if (sum < asteroid)
                        return false;
                    sum += asteroid;
                }
                return true;
            }
        };
    }

    namespace task_2130
    {
        /*
		* https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/description/
		*/
        class Solution
        {
            public int PairSum(ListNode head)
            {
                var middle = FindMiddle(head);
                var reversed = Reverse(middle.next);
                int max_sum = 0;
                while (reversed != null)
                {
                    max_sum = Math.Max(max_sum, head.val + reversed.val);
                    head = head.next;
                    reversed = reversed.next;
                }
                return max_sum;
            }

            public ListNode Reverse(ListNode head)
            {
                if (head == null)
                    return null;
                ListNode next = head.next;
                head.next = null;

                while (next != null)
                {
                    ListNode temp = next.next;
                    next.next = head;
                    head = next;
                    next = temp;
                }
                return head;
            }

            public ListNode FindMiddle(ListNode head)
            {
                if (head == null)
                    return null;
                ListNode fast = head, slow = head;

                while (fast.next != null && fast.next.next != null)
                {
                    slow = slow.next;
                    fast = fast.next.next;
                }
                return slow;
            }
        };
    }

    namespace task_2144
    {
        /*
		* https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/description/
		*/
        class Solution
        {
            public int AsteroidsDestroyed(int[] cost)
            {
                Array.Sort(cost);
                int sum = 0;
				int i = cost.Length - 1;
                for (; i > 1; i -= 3)
                    sum += cost[i] + cost[i - 1];
                for (; i > -1; --i)
                    sum += cost[i];
                return sum;
            }
        };
    }

    namespace task_3093
	{
		/*
		* https://leetcode.com/problems/longest-common-suffix-queries/description/
		*/
		public class Solution
		{
			public class Trie
			{
				public class Node
				{
					public Dictionary<char, Node> children = new Dictionary<char, Node>();
					public int length = Int32.MaxValue;
					public int index = 0;
				};
				public Node root;

				public Trie() {
					root = new Node();
				}

				public void Insert(string word, int index)
				{
					Node node = root;
					int size = word.Length;
					if (node.length > size)
					{
						node.length = size;
						node.index = index;
					}
					for (int i = size - 1; i > -1; --i)
					{
						char c = word[i];
						if (!node.children.ContainsKey(c))
							node.children.Add(c, new Node());

						node = node.children[c];
						if (node.length > size)
						{
							node.length = size;
							node.index = index;
						}
					}
				}

				public int Search(string word)
				{
					Node node = root;
					int size = word.Length;
					int res = node.index;
					for (int i = size - 1; i > -1; --i)
					{
						char c = word[i];
						if (!node.children.ContainsKey(c))
							return res;
						node = node.children[c];
						res = node.index;
					}
					return res;
				}

				public void Clear()
				{
					root.children.Clear();
				}
			};

			public int[] StringIndices(string[] wordsContainer, string[] wordsQuery)
			{
				Trie trie = new Trie();
				int size = wordsContainer.Length;
				for (int i = 0; i < size; ++i)
					trie.Insert(wordsContainer[i], i);

				size = wordsQuery.Length;
				int[] res = new int[size];
				for (int i = 0; i < size; ++i)
					res[i] = trie.Search(wordsQuery[i]);
				trie.Clear();
				return res;
			}
		}
	}

    namespace task_3310
    {
        /*
		* https://leetcode.com/problems/remove-methods-from-project/description/
		*/
        public class Solution
        {
            public IList<int> RemainingMethods(int n, int k, int[][] invocations)
            {
                var adjacency_list = GetAdjacencyList(invocations, n);
                var visited = new int[n];
                int vertex = 0;

                Queue<int> queue = new();
                queue.Enqueue(k);
                visited[k] = 1;
                while (queue.Count != 0)
                {
                    vertex = queue.Dequeue();
                    foreach (int neighbour in adjacency_list[vertex])
                    {
                        if (visited[neighbour] == 0)
                        {
                            visited[neighbour] = 1;
                            queue.Enqueue(neighbour);
                        }
                    }
                }


                bool is_not_removed = true;
                for (int i = 0; i < n && is_not_removed; i++)
                {
                    if (visited[i] == 0)
                    {
                        visited[i] = 2;
                        queue.Enqueue(i);
                        while (queue.Count != 0 && is_not_removed)
                        {
                            vertex = queue.Dequeue();
                            foreach (int neighbour in adjacency_list[vertex])
                            {
                                if (visited[neighbour] == 1)
                                {
                                    is_not_removed = false;
                                    break;
                                }
                                if (visited[neighbour] != 2)
                                {
                                    visited[neighbour] = 2;
                                    queue.Enqueue(neighbour);
                                }
                            }
                        }
                    }
                }

                var answer = new List<int>();

                if (is_not_removed)
                {
                    for (int i = 0; i < n; i++)
                    {
                        if (visited[i] == 2)
                            answer.Add(i);
                    }
                }
                else
                {
                    for (int i = 0; i < n; i++)
                    {
                        answer.Add(i);
                    }
                }
                    
                return answer;
            }

            public static List<int>[] GetAdjacencyList(int[][] edges, int vertexes)
            {
                var adjacency_list = new List<int>[vertexes];
                for (int i = 0; i < vertexes; i++)
                    adjacency_list[i] = new List<int>();
                foreach (var edge in edges)
                    adjacency_list[edge[0]].Add(edge[1]);
                return adjacency_list;
            }
        };
    }

    namespace task_3330
    {
        /*
		* https://leetcode.com/problems/minimum-element-after-replacement-with-digit-sum/description/
		*/
        public class Solution
        {
            public int MinElement(int[] nums)
            {
                int min_sum = 10000;
                foreach (int num in nums)
                {
					int n = num;
                    int sum = 0;
                    while (n > 0)
                    {
                        sum += n % 10;
                        n /= 10;
                    }
                    if (sum < min_sum)
                        min_sum = sum;
                }
                return min_sum;
            }
        }
    }

    namespace task_3345
    {
        /*
		* https://leetcode.com/problems/minimum-element-after-replacement-with-digit-sum/description/
		*/
        public class Solution
        {
            public int SmallestNumber(int n, int t)
            {
                while (true)
                {
                    if (GetDigitProd(n) % t == 0)
                        return n;
                    n++;
                }
            }

            public int GetDigitProd(int n)
            {
                int prod = 1;
                while (n > 0)
                {
                    prod *= n % 10;
                    n /= 10;
                }
                return prod;
            }
        }
    }

    namespace task_3558
    {
        /*
		* https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/description/
		*/
        public class Solution
        {
            int mod = 1000000007;

            public int AssignEdgeWeights(int[][] edges)
            {
                int size = edges.Length + 2;
                var adjacency_list = GetAdjacencyList(edges, size);

                var degrees = new int[size];
                foreach (var edge in edges)
                    ++degrees[edge[1]];
                int vertex = 0;
                for (int i = 1; i < size; i++)
                {
                    if (degrees[i] == 0)
                    {
                        vertex = i;
                        break;
                    }
                }

                Queue<int> queue = new();
                queue.Enqueue(vertex);
                int depth = -2;
                while (queue.Count != 0)
                {
                    ++depth;
                    size = queue.Count;
                    for (int j = 0; j < size; ++j)
                    {
                        vertex = queue.Dequeue();
                        foreach (int neighbour in adjacency_list[vertex])
                            queue.Enqueue(neighbour);
                    }
                }

                int answer = 1;
                while (depth != 0)
                {
                    answer <<= 1;
                    answer %= mod;
                    --depth;
                }
                return answer;
            }

            public static List<int>[] GetAdjacencyList(int[][] edges, int vertexes)
            {
                var adjacency_list = new List<int>[vertexes];
                for (int i = 1; i < vertexes; i++)
                    adjacency_list[i] = new List<int>();
                foreach (var edge in edges)
                    adjacency_list[edge[0]].Add(edge[1]);
                return adjacency_list;
            }
        };
    }

    namespace task_3612
    {
        /*
		* https://leetcode.com/problems/process-string-with-special-operations-i/description/
		*/
        public class Solution
        {
            public string ProcessStr(string s)
            {
                StringBuilder res = new();
                foreach (char c in s) {
                        if (c == '*')
                        {
                            if (res.Length != 0)
                                res.Length--;
                        }
                        else if (c == '#')
                        {
                            res = res.Append(res);
                        }
                        else if (c == '%')
                        {
                            Reverse(res) ;
                        }
                        else
                        {
                            res.Append(c);
                        }
                }
                return res.ToString();
            }

            public static void Reverse(StringBuilder sb)
            {
                char t;
                int end = sb.Length - 1;
                int start = 0;

                while (end - start > 0)
                {
                    t = sb[end];
                    sb[end] = sb[start];
                    sb[start] = t;
                    start++;
                    end--;
                }
            }
        };
    }

    namespace task_3614
    {
        /*
		* https://leetcode.com/problems/process-string-with-special-operations-ii/description/
		*/
        public class Solution
        {
            public char ProcessStr(string s, long k)
            {
                long len = 0;
                foreach (char c in s)
                {
                    if (c == '*')
                    {
                        if (len != 0)
                            --len;
                    }
                    else if (c == '#')
                    {
                        len <<= 1;
                    }
                    else if (c != '%')
                    {
                        ++len;
                    }
                }
                if (k + 1 > len)
                {
                    return '.';
                }

                for (int i = s.Length - 1; i >= 0; --i)
                {
                    char c = s[i];
                    if (c == '*')
                    {
                        len++;
                    }
                    else if (c == '#')
                    {
                        len >>= 1;
                        if (k >= len)
                            k -= len;
                    }
                    else if (c == '%')
                    {
                        k = len - k - 1;
                    }
                    else
                    {
                        if (len != 0)
                            --len;
                        if (len == k)
                            return s[i];
                    }
                }
                return '.';
            }
        };
    }

    namespace task_3633
    {
        /*
		* https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-i/description/
		*/
        public class Solution
        {
			public int EarliestFinishTime(int[] landStartTime, int[] landDuration, int[] waterStartTime, int[] waterDuration)
            {
                return Math.Min(Solve(landStartTime, landDuration, waterStartTime, waterDuration),
                        Solve(waterStartTime, waterDuration, landStartTime, landDuration));
            }

            public static int Solve(int[] start1, int[] duration1, int[] start2, int[] duration2)
            {
                int size = start1.Length;
                int finish1 = Int32.MaxValue;
                for (int i = 0; i < size; ++i)
                    finish1 = Math.Min(finish1, start1[i] + duration1[i]);

                int finish2 = Int32.MaxValue;
                size = start2.Length;
                for (int i = 0; i < size; ++i)
                    finish2 = Math.Min(finish2, Math.Max(start2[i], finish1) + duration2[i]);
                return finish2;
            }
        };
    }

    namespace task_3635
    {
        /*
		* https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-ii/description/
		*/
        public class Solution
        {
            public int EarliestFinishTime(int[] landStartTime, int[] landDuration, int[] waterStartTime, int[] waterDuration)
            {
                return Math.Min(Solve(landStartTime, landDuration, waterStartTime, waterDuration),
                        Solve(waterStartTime, waterDuration, landStartTime, landDuration));
            }

            public static int Solve(int[] start1, int[] duration1, int[] start2, int[] duration2)
            {
                int size = start1.Length;
                int finish1 = Int32.MaxValue;
                for (int i = 0; i < size; ++i)
                    finish1 = Math.Min(finish1, start1[i] + duration1[i]);

                int finish2 = Int32.MaxValue;
                size = start2.Length;
                for (int i = 0; i < size; ++i)
                    finish2 = Math.Min(finish2, Math.Max(start2[i], finish1) + duration2[i]);
                return finish2;
            }
        };
    }

    namespace task_3689
    {
        /*
		* https://leetcode.com/problems/maximum-total-subarray-value-i/description/
		*/
        public class Solution
        {
            public long MaxTotalValue(int[] nums, int k)
            {
                long max = nums.Max();
                long min = nums.Min();
                return (max - min) * k;
            }
        };
    }

    namespace task_3731
    {
        /*
		* https://leetcode.com/problems/find-missing-elements/description/
		*/
        public class Solution
        {
            public IList<int> FindMissingElements(int[] nums)
            {
                Array.Sort(nums);
                var res = new List<int>();
                int ind = 0, last = nums[nums.Length - 1] + 1;
                for (int i = nums[0]; i < last; ++i)
                {
                    if (nums[ind] == i) {
                        ++ind;
                    }
                    else
                    {
                        res.Add(i);
                    }
                }
                return res;
            }
        };
    }

    namespace task_3904
    {
        /*
		* https://leetcode.com/problems/smallest-stable-index-ii/description/
		*/
        public class Solution
        {
            public int FirstStableIndex(int[] nums, int k)
            {
                int n = nums.Length;
                var minValue = new Stack<int>();
                minValue.Push(nums[n - 1]);
                for (int i = n - 2; i >= 0; i--)
                {
                    minValue.Push(Math.Min(minValue.Peek(), nums[i]));
                }

                int maxValue = 0;
                for (int i = 0; i < n; i++)
                {
                    maxValue = Math.Max(maxValue, nums[i]);
                    if (maxValue - minValue.Pop() <= k)
                    {
                        return i;
                    }
                }
                return -1;
            }
        };
    }
}
