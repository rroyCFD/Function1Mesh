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

#include "damp.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

void Foam::Function1MeshTypes::damp::read(
    const dictionary& coeffs, const fvMesh& mesh)
{
    start_ = coeffs.lookupOrDefault<scalar>("start", 0);
    // duration_ = coeffs.lookupType<scalar>("duration");
    thresholdValue_ = coeffs.lookupType<scalar>("thresholdValue");
    maxValue_ = coeffs.lookupOrDefault<scalar>("maxValue", 1);

    if(thresholdValue_ > maxValue_)
    {
        Info << "thresholdValue: " << thresholdValue_ << tab
             << "maxValue: " << maxValue_ << endl;

        FatalErrorInFunction
            << "threshold value is larger than maximum value!"
            << abort(FatalError);
    }
}


Foam::Function1MeshTypes::damp::damp
(
    const word& entryName,
    const dictionary& dict,
    const fvMesh& mesh
)
:
    Function1Mesh<scalar>(entryName)
{
    read(dict, mesh);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::Function1MeshTypes::damp::~damp()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::Function1MeshTypes::damp::writeData(Ostream& os) const
{
    Function1Mesh<scalar>::writeData(os);
    os  << token::END_STATEMENT << nl;
    os  << indent << word(this->name() + "Coeffs") << nl;
    os  << indent << token::BEGIN_BLOCK << incrIndent << nl;
    os.writeKeyword("start") << start_ << token::END_STATEMENT << nl;
    // os.writeKeyword("duration") << duration_ << token::END_STATEMENT << nl;
    os.writeKeyword("thresholdValue") << thresholdValue_
     << token::END_STATEMENT << nl;
    os.writeKeyword("maxValue") << maxValue_ << token::END_STATEMENT << nl;
    os  << decrIndent << indent << token::END_BLOCK << endl;
}


// ************************************************************************* //
