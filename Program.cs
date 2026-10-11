using System;
using System.Buffers;
using System.Collections.Generic;
using System.Diagnostics.Metrics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;

namespace CS_practice
{
	class Program
	{
		private const int MinBufferSize = 2014;
		static async Task<long> CountSymbols(Stream source, Thread reference)
		{
			Console.Write(ReferenceEquals(Thread.CurrentThread, reference) ? "same " : "other");

			var count = 0L;

			var buffer = ArrayPool<byte>.Shared.Rent(MinBufferSize);
			try
			{
				while (true)
				{
					var bytesRead = await source.ReadAsync(buffer, 0, buffer.Length);

					if (0 == bytesRead)
					{
						break;
					}

					count += bytesRead;
				}
			}
			finally
			{
				ArrayPool<byte>.Shared.Return(buffer);
			}

			Console.Write(ReferenceEquals(Thread.CurrentThread, reference) ? "same " : "other");

			return count;
		}

		static void Main(string[] args)
		{
			var t2 = new Test2();
            Test1 t1 = t2;
            t2.TestMethod();
            t1.TestMethod();
			return;

            var thisAssemblyFilePath = new UriBuilder(Assembly.GetExecutingAssembly().CodeBase).Path;

			using (var assembly = new MemoryStream(new byte[31]))
			{
				CountSymbols(assembly, Thread.CurrentThread).Wait();
			}
            var aboveTheLimit = (double value) => value > 300000.0;

            //Console.WriteLine("Hello World!");
        }

        static void Func(in int j)
		{
			//j = 5;
        }

        private static void Display<T>(System.Collections.Generic.IEnumerable<T> values)
		{
			using (var it = values.GetEnumerator())
			{
				int counter = 0;
				while (counter < 10 && it.MoveNext())
				{
					object current = it.Current;

					if (current != null)
						System.Console.Write(current.ToString());
					++counter;
				}
			}
		}

		private static System.Collections.Generic.IEnumerable<long> Even()
		{
			long num = 0;
			while (true)
			{
				yield return num;
				num += 2;
			}
		}

		static async Task TransferSymbols(Stream source, Stream destination)
		{
			byte[] buf = new byte[1];
			while (await source.ReadAsync(buf.AsMemory(0, 1)) > 0)
			{
				if (buf[0] >= 'a' && buf[0] <= 'z')
				{
					await destination.WriteAsync(buf.AsMemory(0, 1));
				}
			}
		}

		static async Task TransferSymbols2(Stream source, Stream destination)
		{
			byte[] buf = new byte[1024];

			int read;

			while ((read = await source.ReadAsync(buf.AsMemory(0, buf.Length))) > 0)
			{
				for (int i = 0; i < read; ++i)
				{
					byte b = buf[i];

					if (b >= 'a' && b <= 'z')
					{
						await destination.WriteAsync(buf.AsMemory(0, buf.Length));
					}
				}
			}
		}


    }

    public static class CompareWithEpsilonExtension
    {
        public static bool CompareWithEpsilon(this double num, double other, double epsilon)
        {
            return Math.Abs(other - num) <= epsilon;
        }

        public static IEnumerable<TP> SelectMany<TS, TP>(this IEnumerable<TS> items, Func<TS, IEnumerable<TP>> produce)
        {
            foreach (var item in items)
            {
                foreach (var produced in produce(item))
                {
                    yield return produced;
                }
            }
        }


        public static IEnumerable<T> Concat<T>(this IEnumerable<T> items1, IEnumerable<T> items2)
        {
            foreach (var item in items1)
            {
                yield return item;
            }
            foreach (var item in items2)
            {
                yield return item;
            }
        }

        public static IEnumerable<TResult> Zip<TL, TR, TResult>(this IEnumerable<TL> left, IEnumerable<TR> right, Func<TL, TR, TResult> glue)
        {
            using var leftIt = left.GetEnumerator();
            using var rightIt = right.GetEnumerator();
            while (leftIt.MoveNext() && rightIt.MoveNext())
            {
                yield return glue(leftIt.Current, rightIt.Current);
            }
        }

        internal sealed class RockStar
        {
            internal string Name { get; set; }
            internal string CurrentBand { get; set; }
            internal string Role { get; set; }
            internal long SalaryPerGig { get; set; }
        }

        internal static RockStar[] stars = new[]
        {
        new RockStar { Name = "Ian Gillan",  CurrentBand = "Deep Purple", SalaryPerGig = 700, Role = "Vocal" },
        new RockStar { Name = "Angus Young",  CurrentBand = "AC/DC", SalaryPerGig = 900, Role = "Guitar" },
        new RockStar { Name = "Roger Glover",  CurrentBand = "Deep Purple", SalaryPerGig = 400, Role = "Bass" },
        new RockStar { Name = "David Coverdale",  CurrentBand = "Whitesnake", SalaryPerGig = 950, Role = "Vocal" },
        new RockStar { Name = "Rick Allen",  CurrentBand = "Def Leppard", SalaryPerGig = 800, Role = "Drums" },
        new RockStar { Name = "Steven J. Morse",  CurrentBand = "Deep Purple", SalaryPerGig = 600, Role = "Guitar" },
        new RockStar { Name = "Don Airey",  CurrentBand = "Deep Purple", SalaryPerGig = 600, Role = "Keyboards" },
        };

		public static IEnumerable<string> GetRockStarsSorted()
		{
			return from star in stars
				   orderby star.SalaryPerGig descending
				   select star.Name;
		}



        public static IEnumerable<object> GetRockStarsDeepPurple()
        {
            return from star in stars
				   where star.CurrentBand == "Deep Purple"
                   select new 
				   {
					   star.Name,
                       Instrument = star.Role
				   };
        }

        public static IEnumerable<object> GetRockStarsGrouped()
        {
            return from star in stars
                   group star by star.CurrentBand into newGroup
                   select new
                   {
                       Name = newGroup.Key,
                       Size = newGroup.Count()
                   };
        }
    }

	public class Test1
	{
		public void TestMethod()
        {
            Console.WriteLine("Test1");
        }
    }

    public class Test2 : Test1
    {
        public new void TestMethod()
        {
            Console.WriteLine("Test2");
        }
    }
}
