import psycopg2

tables = ['students', 'courses', 'enrollments', 'faculty', 'labs']

try:
    conn = psycopg2.connect(
        dbname="testdb",
        user="postgres", 
        password="kika123",
        host="localhost"
    )
    cursor = conn.cursor()

    for table in tables:
        print(f"\n--- {table.upper()} ---")
        cursor.execute(f"SELECT * FROM {table}")
        rows = cursor.fetchall()
        colnames = [desc[0] for desc in cursor.description]
        print("\t".join(colnames))
        for row in rows:
            print("\t".join(map(str, row)))

    cursor.close()
    conn.close()

except Exception as e:
    print("Error:", e)

