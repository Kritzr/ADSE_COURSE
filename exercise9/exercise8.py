import pandas as pd
import numpy as np

# Sample marketing dataset
data = pd.DataFrame({
    'CustomerID': range(1, 11),
    'Region': ['North', 'South', 'East', 'North', 'South', 'West', 'East', 'West', 'North', 'South'],
    'Product': ['Phone', 'TV', 'Phone', 'Laptop', 'TV', 'Phone', 'Laptop', 'TV', 'Laptop', 'Phone'],
    'Gender': ['F', 'M', 'M', 'F', 'F', 'M', 'F', 'M', 'F', 'M'],
    'Purchased': ['Yes', 'No', 'Yes', 'Yes', 'No', 'Yes', 'No', 'Yes', 'Yes', 'No']
})

print("Original Dataset:")
print(data)

# Bitmap generator
def create_bitmaps(column):
    bitmaps = {}
    for val in column.unique():
        bitmaps[val] = np.array(column == val, dtype=int)
    return bitmaps

# Create bitmap indexes
region_bm = create_bitmaps(data['Region'])
product_bm = create_bitmaps(data['Product'])
gender_bm = create_bitmaps(data['Gender'])
purchase_bm = create_bitmaps(data['Purchased'])

# Sample Query: Female customers from North OR who purchased a Phone
result_bitmap = (gender_bm['F'] & region_bm['North']) | product_bm['Phone']
filtered_data = data[result_bitmap.astype(bool)]

print("\nFiltered Result (F from North OR purchased Phone):")
print(filtered_data)

