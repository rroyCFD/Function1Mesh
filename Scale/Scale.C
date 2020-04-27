/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "Scale.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
void Foam::Function1MeshTypes::Scale<Type>::read(
    const dictionary& coeffs, const fvMesh& mesh)
{
    scale_ = Function1Mesh<scalar>::New("scale", coeffs, mesh);
    value_ = Function1Mesh<Type>::New("value", coeffs, mesh);
}


template<class Type>
Foam::Function1MeshTypes::Scale<Type>::Scale
(
    const word& entryName,
    const dictionary& dict,
    const fvMesh& mesh
)
:
    Function1Mesh<Type>(entryName)
{
    read(dict, mesh);
}


template<class Type>
Foam::Function1MeshTypes::Scale<Type>::Scale(const Scale<Type>& se)
:
    Function1Mesh<Type>(se),
    scale_(se.scale_, false),
    value_(se.value_, false)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
Foam::Function1MeshTypes::Scale<Type>::~Scale()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void Foam::Function1MeshTypes::Scale<Type>::writeData(Ostream& os) const
{
    Function1Mesh<Type>::writeData(os);
    os  << token::END_STATEMENT << nl;
    os  << indent << word(this->name() + "Coeffs") << nl;
    os  << indent << token::BEGIN_BLOCK << incrIndent << nl;
    scale_->writeData(os);
    value_->writeData(os);
    os  << decrIndent << indent << token::END_BLOCK << endl;
}


// ************************************************************************* //
