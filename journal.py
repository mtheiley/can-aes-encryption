import numpy as np
from bokeh.plotting import figure, output_file, save
from bokeh.models import ColumnDataSource
import bokeh

bokeh.settings.validation_level = "none"


def create_clean_plot(file_path):
    print("🚀 Loading 10M comma-separated values...")

    # Read entire file as one string
    with open(file_path, "r") as f:
        raw = f.read().strip()

    # Split into numeric values
    ms = np.array(raw.split(","), dtype=np.float64) / 1000
    x = np.arange(len(ms), dtype=np.int64)

    print(f"📊 Samples: {len(ms):,}")
    print(f"Min: {ms.min():.3f} ms")
    print(f"Max: {ms.max():.3f} ms")

    output_file("final_report.html")

    source = ColumnDataSource(dict(x=x, y=ms))

    p = figure(
        title=f"Performance Report ({len(ms):,} Samples)",
        width=1000,
        height=500,
        tools="pan,wheel_zoom,reset",
        output_backend="webgl",  # GPU acceleration
    )

    p.line("x", "y", source=source, line_width=1)

    p.x_range.start = 0
    p.x_range.end = len(ms)
    p.y_range.start = float(ms.min())
    p.y_range.end = float(ms.max())

    print("📁 Saving HTML...")
    save(p)
    print("✅ Done. Open final_report.html")


if __name__ == "__main__":
    create_clean_plot("journal.csv")