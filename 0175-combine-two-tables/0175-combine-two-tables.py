import pandas as pd

def combine_two_tables(person: pd.DataFrame, address: pd.DataFrame) -> pd.DataFrame:
    print(person)
    return pd.merge(person, address, how='left', on='personId')[['firstName', 'lastName', 'city', 'state']]